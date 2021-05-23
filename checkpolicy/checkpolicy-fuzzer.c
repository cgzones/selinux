#include <ctype.h>
#include <getopt.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <netinet/in.h>
#ifndef IPPROTO_DCCP
#define IPPROTO_DCCP 33
#endif
#ifndef IPPROTO_SCTP
#define IPPROTO_SCTP 132
#endif
#include <arpa/inet.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <sys/mman.h>

#include <sepol/module_to_cil.h>
#include <sepol/kernel_to_cil.h>
#include <sepol/kernel_to_conf.h>
#include <sepol/debug.h>
#include <sepol/policydb/policydb.h>
#include <sepol/policydb/services.h>
#include <sepol/policydb/conditional.h>
#include <sepol/policydb/hierarchy.h>
#include <sepol/policydb/expand.h>
#include <sepol/policydb/link.h>

#include "queue.h"
#include "checkpolicy.h"
#include "parse_util.h"

static policydb_t policydb;
static sidtab_t sidtab;

extern policydb_t *policydbp;
extern int mlspol;
extern int werror;

//static int handle_unknown = SEPOL_DENY_UNKNOWN;

unsigned int policyvers = 0;

extern int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size);

/*static int check_level(hashtab_key_t key, hashtab_datum_t datum, void *arg __attribute__ ((unused)))
{
	level_datum_t *levdatum = (level_datum_t *) datum;

	if (!levdatum->isalias && !levdatum->defined) {
		fprintf(stderr,
			"Error:  sensitivity %s was not used in a level definition!\n",
			key);
		return -1;
	}
	return 0;
}*/

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
	//policydb_t parse_policy;
	//int target = SEPOL_TARGET_SELINUX;
	struct policy_file pf;
	FILE *dev_null = NULL;

	/*while ((ch = getopt_long(argc, argv, "o:t:dbU:MCFSVc:OEh", long_options, NULL)) != -1) {
		switch (ch) {
		case 'o':
			outfile = optarg;
			break;
		case 't':
			if (!strcasecmp(optarg, "Xen"))
				target = SEPOL_TARGET_XEN;
			else if (!strcasecmp(optarg, "SELinux"))
				target = SEPOL_TARGET_SELINUX;
			else{
				fprintf(stderr, "%s:  Unknown target platform:"
					"%s\n", argv[0], optarg);
				exit(1);
			}
			break;
		case 'b':
			binary = 1;
			file = binfile;
			break;
		case 'd':
			debug = 1;
			break;
		case 'V':
			show_version = 1;
			break;
		case 'U':
			if (!strcasecmp(optarg, "deny")) {
				handle_unknown = DENY_UNKNOWN;
				break;
			}
			if (!strcasecmp(optarg, "allow")) {
				handle_unknown = ALLOW_UNKNOWN;
				break;
			}
			if (!strcasecmp(optarg, "reject")) {
				handle_unknown = REJECT_UNKNOWN;
				break;
			}
			usage(argv[0]);
		case 'S':
			sort = 1;
			break;
		case 'O':
			optimize = 1;
			break;
		case 'M':
			mlspol = 1;
			break;
		case 'C':
			cil = 1;
			break;
		case 'F':
			conf = 1;
			break;
		case 'c':{
				long int n;
				errno = 0;
				n = strtol(optarg, NULL, 10);
				if (errno) {
					fprintf(stderr,
						"Invalid policyvers specified: %s\n",
						optarg);
					usage(argv[0]);
					exit(1);
				}
				if (n < POLICYDB_VERSION_MIN
				    || n > POLICYDB_VERSION_MAX) {
					fprintf(stderr,
						"policyvers value %ld not in range %d-%d\n",
						n, POLICYDB_VERSION_MIN,
						POLICYDB_VERSION_MAX);
					usage(argv[0]);
					exit(1);
				}
				policyvers = n;
				break;
			}
		}
	}*/

	werror = 1;
	sepol_debug(0);
	sepol_set_policydb(&policydb);
	sepol_set_sidtab(&sidtab);

	/*if (cil && conf) {
		fprintf(stderr, "Can't convert to CIL and policy.conf at the same time\n");
		exit(1);
	}*/

	policy_file_init(&pf);
	pf.type = PF_USE_MEMORY;
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wcast-qual"
	pf.data = (char *) data;
#pragma clang diagnostic pop
	pf.len = size;

	if (policydb_init(&policydb))
		goto exit;

	if (policydb_read(&policydb, &pf, 1))
		goto exit;

	policydbp = &policydb;

	// Check only mls policies
	if (!policydbp->mls)
		goto exit;

	// Check only latest policy version
	policydbp->policyvers = POLICYDB_VERSION_MAX;


	// TODO: non binary
// 	} else {
// 		if (conf) {
// 			fprintf(stderr, "Can only generate policy.conf from binary policy\n");
// 			exit(1);
// 		}
// 		if (policydb_init(&parse_policy))
// 			exit(1);
// 		/* We build this as a base policy first since that is all the parser understands */
// 		parse_policy.policy_type = POLICY_BASE;
// 		policydb_set_target_platform(&parse_policy, target);
//
// 		/* Let sepol know if we are dealing with MLS support */
// 		parse_policy.mls = mlspol;
// 		parse_policy.handle_unknown = handle_unknown;
//
// 		policydbp = &parse_policy;
//
// 		if (read_source_policy(policydbp, file, "checkpolicy") < 0)
// 			exit(1);
//
// 		if (hashtab_map(policydbp->p_levels.table, check_level, NULL))
// 			exit(1);
//
// 		/* Linking takes care of optional avrule blocks */
// 		if (link_modules(NULL, policydbp, NULL, 0, 0)) {
// 			fprintf(stderr, "Error while resolving optionals\n");
// 			exit(1);
// 		}
//
// 		if (!cil) {
// 			if (policydb_init(&policydb)) {
// 				fprintf(stderr, "%s:  policydb_init failed\n", argv[0]);
// 				exit(1);
// 			}
// 			if (expand_module(NULL, policydbp, &policydb, 0, 1)) {
// 				fprintf(stderr, "Error while expanding policy\n");
// 				exit(1);
// 			}
// 			policydb_destroy(policydbp);
// 			policydbp = &policydb;
// 		}
//
// 		policydbp->policyvers = policyvers ? policyvers : POLICYDB_VERSION_MAX;
// 	}

	if (policydb_load_isids(&policydb, &sidtab))
		goto exit;

	if (policydbp->policy_type == POLICY_KERN) {
		if (policydb_optimize(policydbp))
			goto exit;
	}

	dev_null = fopen("/dev/null", "w");
	if (dev_null == NULL)
		goto exit;


	policydb.policy_type = POLICY_KERN;
	policy_file_init(&pf);
	pf.type = PF_USE_STDIO;
	pf.fp = dev_null;

	if (policydb_sort_ocontexts(&policydb))
		goto exit;

	if (policydb_write(&policydb, &pf))
		goto exit;


	/* TODO non binary */
	//ret = sepol_kernel_policydb_to_conf(outfp, policydbp);

	/* TODO cil
	} else {
		if (binary) {
			ret = sepol_kernel_policydb_to_cil(outfp, policydbp);
		} else {
			ret = sepol_module_policydb_to_cil(outfp, policydbp, 1);
		}
		if (ret) {
			fprintf(stderr, "%s:  error writing %s\n", argv[0], outfile);
			exit(1);
		}
	}*/

exit:
	if (dev_null != NULL)
		fclose(dev_null);

	policydb_destroy(&policydb);
	sepol_sidtab_destroy(&sidtab);

	return 0;
}
