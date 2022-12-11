#include "sepol/policydb.h"
#include <errno.h>
#include <getopt.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#include <sepol/policydb/policydb.h>
#include <sepol/policydb/services.h>
#include <sepol/sepol.h>


static int parse_policy(const char *infile, off_t *size, sepol_policydb_t *policydb)
{
	FILE *fp;
	sepol_policy_file_t *pf = NULL;
	struct stat st;
	int rc = -1;

	fp = fopen(infile, "re");
	if (!fp) {
		fprintf(stderr, "failed to open input policy %s:  %m\n", infile);
		goto out;
	}

	if (fstat(fileno(fp), &st) < 0) {
		fprintf(stderr, "failed to stat input policy %s:  %m\n", infile);
		goto out;
	}
	*size = st.st_size;

	if (sepol_policy_file_create(&pf) < 0) {
		fprintf(stderr, "failed to create policy file object:  %m\n");
		goto out;
	}

	sepol_policy_file_set_fp(pf, fp);

	if (sepol_policydb_read(policydb, pf) < 0) {
		fprintf(stderr, "failed to read policy from %s:  %m\n", infile);
		goto out;
	}

	rc = 0;

out:
	if (pf)
		sepol_policy_file_free(pf);
	if (fp)
		fclose(fp);
	return rc;
}

static int write_policy(const char *outfile, off_t *size, sepol_policydb_t *policydb)
{
	FILE *fp;
	sepol_policy_file_t *pf = NULL;
	struct stat st;
	int rc = -1;

	fp = fopen(outfile, "we");
	if (!fp) {
		fprintf(stderr, "failed to open output file %s:  %m\n", outfile);
		goto out;
	}

	if (sepol_policy_file_create(&pf) < 0) {
		fprintf(stderr, "failed to create policy file object:  %m\n");
		goto out;
	}

	sepol_policy_file_set_fp(pf, fp);

	if (sepol_policydb_write(policydb, pf) < 0) {
		fprintf(stderr, "failed to write policy to %s:  %m\n", outfile);
		goto out;
	}

	if (fstat(fileno(fp), &st) < 0) {
		fprintf(stderr, "failed to stat written policy %s:  %m\n", outfile);
		goto out;
	}
	*size = st.st_size;

	rc = 0;

out:
	if (pf)
		sepol_policy_file_free(pf);
	if (fp)
		fclose(fp);
	return rc;
}

static void usage(void)
{
	printf("\nUsage: sepol_optimize [OPTION] input_policy -o output_policy\n\n");
	printf("  -i  Optimize the policy in place.\n");
	printf("  -q  Hide verbose output.\n");
	printf("  -h  This help message.\n");
}

int main(int argc, char *argv[])
{
	bool inplace = false, quiet = false;
	const char *in_policy = NULL;
	const char *out_policy = NULL;
	int opt;
	sepol_policydb_t *policydb = NULL;
	off_t in_size, out_size;

	while (1) {
		opt = getopt(argc, argv, "hio:v");
		if (opt == -1)
			break;
		switch (opt) {
		case 'h':
			usage();
			return EXIT_SUCCESS;
		case 'i':
			if (out_policy) {
				fprintf(stderr, "options -i and -o are mutual exclusive\n");
				return EXIT_FAILURE;
			}
			inplace = true;
			break;
		case 'o':
			if (inplace) {
				fprintf(stderr, "options -i and -o are mutual exclusive\n");
				return EXIT_FAILURE;
			}
			out_policy = optarg;
			break;
		case 'q':
			quiet = true;
			break;
		default:
			/* invalid option */
			usage();
			return EXIT_FAILURE;
		}
	}

	if (!out_policy && !inplace) {
		fprintf(stderr, "no output path given\n");
		usage();
		return EXIT_FAILURE;
	}

	if (optind != argc - 1) {
		usage();
		return EXIT_FAILURE;
	}

	in_policy = argv[optind];
	if (inplace)
		out_policy = in_policy;

	if (!quiet)
		printf("optimizing policy %s to %s\n", in_policy, out_policy);

	if (sepol_policydb_create(&policydb) < 0) {
		fprintf(stderr, "failed to create policy database object:  %m\n");
		return EXIT_FAILURE;
	}

	if (parse_policy(in_policy, &in_size, policydb) < 0) {
		sepol_policydb_free(policydb);
		return EXIT_FAILURE;
	}

	if (sepol_policydb_optimize(policydb) < 0) {
		fprintf(stderr, "failed to optimize policy\n");
		sepol_policydb_free(policydb);
		return EXIT_FAILURE;
	}

	if (sepol_policydb_validate(NULL, policydb) < 0) {
		fprintf(stderr, "failed to validate optimized policy\n");
		sepol_policydb_free(policydb);
		return EXIT_FAILURE;
	}

	if (write_policy(out_policy, &out_size, policydb) < 0) {
		sepol_policydb_free(policydb);
		return EXIT_FAILURE;
	}

	sepol_policydb_free(policydb);

	if (!quiet)
		printf("Saved %zu bytes (%zu to %zu ~= %.1f%%)\n", in_size - out_size, in_size, out_size, 100.0F * (float)(in_size - out_size) / (float)in_size);

	return EXIT_SUCCESS;
}
