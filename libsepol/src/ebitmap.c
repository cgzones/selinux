
/* Author : Stephen Smalley, <stephen.smalley.work@gmail.com> */

/* FLASK */

/* 
 * Implementation of the extensible bitmap type.
 */

#include <assert.h>
#include <stdlib.h>

#include <sepol/policydb/ebitmap.h>
#include <sepol/policydb/policydb.h>

#include "debug.h"
#include "private.h"

#define NODES_INITIAL_CAPACITY 4

static int grow_nodes_vec(ebitmap_t * dst)
{
	uint32_t new_cap;
	ebitmap_node_t *tmp;

	if (dst->size < dst->capacity)
		return 0;

	new_cap = dst->capacity + (dst->capacity >> 1) + (dst->capacity >> 4) + 4;
	if (new_cap < dst->capacity)
		return -EOVERFLOW;

	tmp = reallocarray(dst->nodes, new_cap, sizeof(*dst->nodes));
	if (!tmp)
		return -ENOMEM;

	dst->nodes = tmp;
	dst->capacity = new_cap;
	return 0;
}

int ebitmap_or(ebitmap_t * restrict dst, const ebitmap_t * restrict e1, const ebitmap_t * restrict e2)
{
	uint32_t cap, it1, it2;

	ebitmap_init(dst);

	if (__builtin_add_overflow(e1->size, e2->size, &cap))
		cap = UINT32_MAX;

	if (cap == 0)
		return 0;

	dst->nodes = malloc(cap * sizeof(*dst->nodes));
	if (!dst->nodes)
		return -ENOMEM;
	dst->capacity = cap;

	for (it1 = 0, it2 = 0; it1 < e1->size || it2 < e2->size;) {
		if (dst->size == UINT32_MAX) {
			ebitmap_destroy(dst);
			return -EOVERFLOW;
		}
		assert(dst->size < dst->capacity);

		if (it1 < e1->size && it2 < e2->size &&
		    e1->nodes[it1].startbit == e2->nodes[it2].startbit) {
			dst->nodes[dst->size++] = (ebitmap_node_t) {
				.startbit = e1->nodes[it1].startbit,
				.map = e1->nodes[it1].map | e2->nodes[it2].map,
			};
			it1++;
			it2++;
		} else if (it2 >= e2->size || (it1 < e1->size && e1->nodes[it1].startbit < e2->nodes[it2].startbit)) {
			dst->nodes[dst->size++] = (ebitmap_node_t) {
				.startbit = e1->nodes[it1].startbit,
				.map = e1->nodes[it1].map,
			};
			it1++;
		} else {
			dst->nodes[dst->size++] = (ebitmap_node_t) {
				.startbit = e2->nodes[it2].startbit,
				.map = e2->nodes[it2].map,
			};
			it2++;
		}
	}

	dst->highbit = MAX(e1->highbit, e2->highbit);
	return 0;
}

int ebitmap_union(ebitmap_t * dst, const ebitmap_t * e1)
{
	ebitmap_t tmp;

	if (ebitmap_or(&tmp, dst, e1))
		return -1;
	ebitmap_destroy(dst);
	*dst = tmp;

	return 0;
}

int ebitmap_and(ebitmap_t * restrict dst, const ebitmap_t * restrict e1, const ebitmap_t * restrict e2)
{
	uint32_t cap, it1, it2;

	ebitmap_init(dst);

	cap = MIN(e1->size, e2->size);

	if (cap == 0)
		return 0;

	dst->nodes = malloc(cap * sizeof(*dst->nodes));
	if (!dst->nodes)
		return -ENOMEM;
	dst->capacity = cap;

	for (it1 = 0, it2 = 0; it1 < e1->size && it2 < e2->size;) {
		if (e1->nodes[it1].startbit == e2->nodes[it2].startbit) {
			if (e1->nodes[it1].map & e2->nodes[it2].map) {
				if (dst->size == UINT32_MAX) {
					ebitmap_destroy(dst);
					return -EOVERFLOW;
				}
				assert(dst->size < dst->capacity);

				dst->nodes[dst->size++] = (ebitmap_node_t) {
					.startbit = e1->nodes[it1].startbit,
					.map = e1->nodes[it1].map & e2->nodes[it2].map,
				};
			}
			it1++;
			it2++;
		} else if (e1->nodes[it1].startbit < e2->nodes[it2].startbit) {
			it1++;
		} else {
			it2++;
		}
	}

	if (dst->size > 0)
		dst->highbit = dst->nodes[dst->size - 1].startbit + MAPSIZE;

	return 0;
}

int ebitmap_xor(ebitmap_t * restrict dst, const ebitmap_t * restrict e1, const ebitmap_t * restrict e2)
{
	uint32_t cap, it1, it2;

	ebitmap_init(dst);

	if (__builtin_add_overflow(e1->size, e2->size, &cap))
		cap = UINT32_MAX;

	if (cap == 0)
		return 0;

	dst->nodes = malloc(cap * sizeof(*dst->nodes));
	if (!dst->nodes)
		return -ENOMEM;
	dst->capacity = cap;

	for (it1 = 0, it2 = 0; it1 < e1->size || it2 < e2->size;) {
		uint32_t startbit;
		MAPTYPE map;

		if (it1 < e1->size && it2 < e2->size &&
		    e1->nodes[it1].startbit == e2->nodes[it2].startbit) {
			startbit = e1->nodes[it1].startbit;
			map = e1->nodes[it1].map ^ e2->nodes[it2].map;
			it1++;
			it2++;
		} else if (it2 >= e2->size || (it1 < e1->size && e1->nodes[it1].startbit < e2->nodes[it2].startbit)) {
			startbit = e1->nodes[it1].startbit;
			map = e1->nodes[it1].map;
			it1++;
		} else {
			startbit = e2->nodes[it2].startbit;
			map = e2->nodes[it2].map;
			it2++;
		}

		if (map != 0) {
			if (dst->size == UINT32_MAX) {
				ebitmap_destroy(dst);
				return -EOVERFLOW;
			}
			assert(dst->size < dst->capacity);

			dst->nodes[dst->size++] = (ebitmap_node_t) {
				.startbit = startbit,
				.map = map,
			};
		}
	}

	if (dst->size > 0)
		dst->highbit = dst->nodes[dst->size - 1].startbit + MAPSIZE;

	return 0;
}

int ebitmap_not(ebitmap_t * restrict dst, const ebitmap_t * restrict e1, unsigned int maxbit)
{
	uint32_t cur_startbit, it;

	ebitmap_init(dst);

	dst->nodes = malloc(NODES_INITIAL_CAPACITY * sizeof(*dst->nodes));
	if (!dst->nodes)
		return -ENOMEM;
	dst->capacity = NODES_INITIAL_CAPACITY;

	for (it = 0, cur_startbit = 0; cur_startbit < maxbit; cur_startbit += MAPSIZE) {
		uint32_t startbit;
		MAPTYPE map;

		if (it < e1->size && e1->nodes[it].startbit == cur_startbit) {
			startbit = e1->nodes[it].startbit;
			map = ~e1->nodes[it].map;

			it++;
		} else {
			startbit = cur_startbit;
			map = ~((MAPTYPE) 0);
		}

		if (maxbit - cur_startbit < MAPSIZE)
			map &= (((MAPTYPE)1) << (maxbit - cur_startbit)) - 1;

		if (map != 0) {
			int r;

			r = grow_nodes_vec(dst);
			if (r < 0) {
				ebitmap_destroy(dst);
				return r;
			}

			dst->nodes[dst->size++] = (ebitmap_node_t) {
				.startbit = startbit,
				.map = map,
			};
		}
	}

	if (dst->size > 0)
		dst->highbit = dst->nodes[dst->size - 1].startbit + MAPSIZE;

	return 0;
}

int ebitmap_andnot(ebitmap_t *dst, const ebitmap_t *e1, const ebitmap_t *e2, unsigned int maxbit)
{
	int rc;
	ebitmap_t e3;
	ebitmap_init(dst);
	rc = ebitmap_not(&e3, e2, maxbit);
	if (rc < 0)
		return rc;
	rc = ebitmap_and(dst, e1, &e3);
	ebitmap_destroy(&e3);
	if (rc < 0)
		return rc;
	return 0;
}

unsigned int ebitmap_cardinality(const ebitmap_t *e1)
{
	unsigned int count = 0;
	uint32_t it;

	for (it = 0; it < e1->size; it++) {
		count += __builtin_popcountll(e1->nodes[it].map);
	}

	return count;
}

int ebitmap_hamming_distance(const ebitmap_t * e1, const ebitmap_t * e2)
{
	int rc;
	ebitmap_t tmp;
	int distance;
	if (ebitmap_cmp(e1, e2))
		return 0;
	rc = ebitmap_xor(&tmp, e1, e2);
	if (rc < 0)
		return -1;
	distance = ebitmap_cardinality(&tmp);
	ebitmap_destroy(&tmp);
	return distance;
}

int ebitmap_cmp(const ebitmap_t * e1, const ebitmap_t * e2)
{
	uint32_t it1, it2;

	if (e1->highbit != e2->highbit || e1->size != e2->size)
		return 0;

	it1 = 0;
	it2 = 0;
	while (it1 < e1->size && it2 < e2->size &&
	       e1->nodes[it1].startbit == e2->nodes[it2].startbit &&
	       e1->nodes[it1].map == e2->nodes[it2].map) {
		it1++;
		it2++;
	}

	if (it1 < e1->size || it2 < e2->size)
		return 0;

	return 1;
}

int ebitmap_cpy(ebitmap_t * restrict dst, const ebitmap_t * restrict src)
{
	uint32_t src_it;

	ebitmap_init(dst);

	dst->nodes = malloc(src->size * sizeof(*dst->nodes));
	if (!dst->nodes)
		return -ENOMEM;
	dst->capacity = src->size;

	for (src_it = 0; src_it < src->size; src_it++) {
		dst->nodes[dst->size++] = (ebitmap_node_t) {
			.startbit = src->nodes[src_it].startbit,
			.map = src->nodes[src_it].map,
		};
	}

	dst->highbit = src->highbit;
	return 0;
}

int ebitmap_contains(const ebitmap_t * e1, const ebitmap_t * e2)
{
	uint32_t it1, it2;

	if (e1->highbit < e2->highbit || e1->size < e2->size)
		return 0;

	it1 = 0;
	it2 = 0;
	while (it1 < e1->size && it2 < e2->size && (e1->nodes[it1].startbit <= e2->nodes[it2].startbit)) {
		if (e1->nodes[it1].startbit < e2->nodes[it2].startbit) {
			it1++;
			continue;
		}

		if ((e1->nodes[it1].map & e2->nodes[it2].map) != e2->nodes[it2].map)
			return 0;

		it1++;
		it2++;
	}

	if (it2 < e2->size)
		return 0;

	return 1;
}

int ebitmap_match_any(const ebitmap_t *e1, const ebitmap_t *e2)
{
	uint32_t it1 = 0, it2 = 0;

	while (it1 < e1->size && it2 < e2->size) {
		if (e1->nodes[it1].startbit < e2->nodes[it2].startbit) {
			it1++;
		} else if (e1->nodes[it1].startbit > e2->nodes[it2].startbit) {
			it2++;
		} else {
			if (e1->nodes[it1].map & e2->nodes[it2].map) {
				return 1;
			}
			it1++;
			it2++;
		}
	}

	return 0;
}

int ebitmap_get_bit(const ebitmap_t * e, unsigned int bit)
{
	uint32_t it = 0;

	if (e->highbit < bit)
		return 0;

	while (it < e->size && (e->nodes[it].startbit <= bit)) {
		if ((e->nodes[it].startbit + MAPSIZE) > bit) {
			if (e->nodes[it].map & (MAPBIT << (bit - e->nodes[it].startbit)))
				return 1;
			else
				return 0;
		}
		it++;
	}

	return 0;
}

int ebitmap_set_bit(ebitmap_t * e, unsigned int bit, int value)
{
	uint32_t it, higher_elems;
	const uint32_t startbit = bit & ~(MAPSIZE - 1);
	const uint32_t highbit = startbit + MAPSIZE;
	int r;

	if (highbit == 0) {
		ERR(NULL, "bitmap overflow, bit 0x%x", bit);
		return -EINVAL;
	}

	for (it = 0; it < e->size && e->nodes[it].startbit <= bit; it++) {
		if ((e->nodes[it].startbit + MAPSIZE) > bit) {
			if (value) {
				e->nodes[it].map |= (MAPBIT << (bit - e->nodes[it].startbit));
			} else {
				e->nodes[it].map &= ~(MAPBIT << (bit - e->nodes[it].startbit));
				if (!e->nodes[it].map) {
					/* drop this node from the bitmap */

					higher_elems = e->size - it - 1;
					if (higher_elems == 0) {
						/*
						 * this was the highest map
						 * within the bitmap
						 */
						e->size--;
						e->highbit = e->size > 0 ? e->nodes[e->size - 1].startbit + MAPSIZE : 0;
					} else {
						memmove(&e->nodes[it], &e->nodes[it + 1], higher_elems * sizeof(*e->nodes));
						e->size--;
					}
				}
			}
			return 0;
		}
	}

	if (!value)
		return 0;

	r = grow_nodes_vec(e);
	if (r < 0)
		return r;

	higher_elems = e->size - it;
	if (higher_elems == 0) {
		e->nodes[e->size++] = (ebitmap_node_t) {
			.startbit = startbit,
			.map = (MAPBIT << (bit - startbit)),
		};
		e->highbit = highbit;
	} else {
		memmove(&e->nodes[it + 1], &e->nodes[it], higher_elems * sizeof(*e->nodes));
		e->nodes[it] = (ebitmap_node_t) {
			.startbit = startbit,
			.map = (MAPBIT << (bit - startbit)),
		};
		e->size++;
	}

	return 0;
}

int ebitmap_init_range(ebitmap_t * e, unsigned int minbit, unsigned int maxbit)
{
	const uint32_t minstartbit = minbit & ~(MAPSIZE - 1);
	const uint32_t maxstartbit = maxbit & ~(MAPSIZE - 1);
	const uint32_t minhighbit = minstartbit + MAPSIZE;
	const uint32_t maxhighbit = maxstartbit + MAPSIZE;
	uint32_t cap, startbit;

	ebitmap_init(e);

	if (minbit > maxbit)
		return -EINVAL;

	if (minhighbit == 0 || maxhighbit == 0)
		return -EOVERFLOW;

	cap = (maxstartbit - minstartbit) / MAPSIZE + 1;
	e->nodes = malloc(cap * sizeof(*e->nodes));
	if (!e->nodes)
		return -ENOMEM;
	e->capacity = cap;

	for (startbit = minstartbit; startbit <= maxstartbit; startbit += MAPSIZE) {
		MAPTYPE map, mask;

		if (startbit != minstartbit && startbit != maxstartbit) {
			map = ~((MAPTYPE)0);
		} else if (startbit != maxstartbit) {
			map = ~((MAPTYPE)0) << (minbit - startbit);
		} else if (startbit != minstartbit) {
			map = ~((MAPTYPE)0) >> (MAPSIZE - (maxbit - startbit + 1));
		} else {
			mask = ~((MAPTYPE)0) >> (MAPSIZE - (maxbit - minbit + 1));
			map = (mask << (minbit - startbit));
		}

		assert(e->size < e->capacity);

		e->nodes[e->size++] = (ebitmap_node_t) {
			.startbit = startbit,
			.map = map,
		};
	}

	e->highbit = maxhighbit;

	return 0;
}

unsigned int ebitmap_highest_set_bit(const ebitmap_t * e)
{
	MAPTYPE map;
	unsigned int pos = 0;

	if (e->size == 0)
		return 0;

	map = e->nodes[e->size - 1].map;
	while (map >>= 1)
		pos++;

	return e->nodes[e->size - 1].startbit + pos;
}

void ebitmap_destroy(ebitmap_t * e)
{
	if (!e)
		return;

	free(e->nodes);
	e->nodes = NULL;
	e->capacity = 0;
	e->size = 0;
	e->highbit = 0;
}

int ebitmap_read(ebitmap_t * e, void *fp)
{
	int rc;
	uint32_t buf[3], mapsize, count, it;

	ebitmap_init(e);

	rc = next_entry(buf, fp, sizeof(uint32_t) * 3);
	if (rc < 0)
		goto bad;

	mapsize = le32_to_cpu(buf[0]);
	e->highbit = le32_to_cpu(buf[1]);
	count = le32_to_cpu(buf[2]);

	if (mapsize != MAPSIZE) {
		ERR(NULL, "security: ebitmap: map size %d does not match my size %zu (high bit was %d)",
		     mapsize, MAPSIZE, e->highbit);
		goto bad;
	}
	if ((e->highbit && !count) || (!e->highbit && count))
		goto bad;
	if (!e->highbit)
		goto ok;
	if (e->highbit & (MAPSIZE - 1)) {
		ERR(NULL, "security: ebitmap: high bit (%d) is not a multiple of the map size (%zu)",
		     e->highbit, MAPSIZE);
		goto bad;
	}

	e->nodes = malloc(count * sizeof(*e->nodes));
	if (!e->nodes)
		goto bad;
	e->capacity = count;

	for (it = 0; it < count; it++) {
		uint64_t map;
		uint32_t startbit;

		rc = next_entry(buf, fp, sizeof(uint32_t));
		if (rc < 0) {
			ERR(NULL, "security: ebitmap: truncated map");
			goto bad;
		}

		startbit = le32_to_cpu(buf[0]);

		if (startbit & (MAPSIZE - 1)) {
			ERR(NULL, "security: ebitmap start bit (%d) is not a multiple of the map size (%zu)",
			     startbit, MAPSIZE);
			goto bad;
		}
		if (startbit > (e->highbit - MAPSIZE)) {
			ERR(NULL, "security: ebitmap start bit (%d) is beyond the end of the bitmap (%zu)",
			     startbit, (e->highbit - MAPSIZE));
			goto bad;
		}
		rc = next_entry(&map, fp, sizeof(uint64_t));
		if (rc < 0) {
			ERR(NULL, "security: ebitmap: truncated map");
			goto bad;
		}
		map = le64_to_cpu(map);

		if (!map) {
			ERR(NULL, "security: ebitmap: null map in ebitmap (startbit %d)",
			     startbit);
			goto bad;
		}
		if (it > 0 && startbit <= e->nodes[it - 1].startbit) {
			ERR(NULL, "security: ebitmap: start bit %d comes after start bit %d",
			     startbit, e->nodes[it - 1].startbit);
			goto bad;
		}

		e->nodes[e->size++] = (ebitmap_node_t) {
			.startbit = startbit,
			.map = map,
		};
	}
	if (e->size && e->nodes[e->size - 1].startbit + MAPSIZE != e->highbit) {
		ERR(NULL, "security: ebitmap: high bit %u has not the expected value %zu",
		     e->highbit, e->nodes[e->size - 1].startbit + MAPSIZE);
		goto bad;
	}

      ok:
	rc = 0;
      out:
	return rc;
      bad:
	if (!rc)
		rc = -EINVAL;
	ebitmap_destroy(e);
	goto out;
}

/* FLASK */
