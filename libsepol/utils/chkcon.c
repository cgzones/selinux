#include <sepol/sepol.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

static void usage(char *progname)
{
	printf("usage:  %s policy context\n", progname);
}

int main(int argc, char **argv)
{
	FILE *fp;

	if (argc != 3) {
		usage(argv[0]);
		return 1;
	}

	fp = fopen(argv[1], "re");
	if (!fp) {
		fprintf(stderr, "Can't open '%s':  %m\n",
			argv[1]);
		return 1;
	}
	if (sepol_set_policydb_from_file(fp) < 0) {
		fprintf(stderr, "Error while processing %s:  %m\n",
			argv[1]);
		return 1;
	}
	fclose(fp);

	if (sepol_check_context(argv[2]) < 0) {
		fprintf(stderr, "%s is not valid\n", argv[2]);
		return 1;
	}

	printf("%s is valid\n", argv[2]);
	return 0;
}
