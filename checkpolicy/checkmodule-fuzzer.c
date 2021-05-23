#define _GNU_SOURCE

#include <unistd.h>
#include <sys/mman.h>

#include <sepol/debug.h>
#include <sepol/policydb/policydb.h>
#include <sepol/policydb/services.h>
#include <sepol/policydb/hierarchy.h>
#include <sepol/policydb/expand.h>
#include <sepol/policydb/link.h>

#include "queue.h"

extern int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size);

extern int mlspol;
extern policydb_t *policydbp;
extern queue_t id_queue;
extern unsigned int policydb_errors;

unsigned int policy_type = POLICY_BASE;
unsigned int policyvers = MOD_POLICYDB_VERSION_MAX;

extern FILE *yyin;
extern void init_parser(int);
extern int yyparse(void);
extern void yyrestart(FILE *);
extern void set_source_file(const char *name);

static int read_source_policy(policydb_t * p, const uint8_t *data, size_t size)
{
	int fd;
	ssize_t wr;

	fd = memfd_create("fuzz-input", MFD_CLOEXEC);
	if (fd < 0)
		abort(); //return -1;

	wr = write(fd, data, size);
	if (wr < 0 || (size_t)wr != size) {
		close(fd);
		abort(); //return -1;
	}

	fsync(fd);

	yyin = fdopen(fd, "r");
	if (!yyin) {
		close(fd);
		abort(); //return -1;
	}

	rewind(yyin);

	set_source_file("fuzz-input");

	if ((id_queue = queue_create()) == NULL) {
		fclose(yyin);
		abort(); //return -1;
	}

	policydbp = p;
	mlspol = p->mls;

	init_parser(1);

	if (yyparse() || policydb_errors) {
		queue_destroy(id_queue);
		fclose(yyin);
		return -1;
	}

	rewind(yyin);
	init_parser(2);
	set_source_file("fuzz-input");
	yyrestart(yyin);

	if (yyparse() || policydb_errors) {
		queue_destroy(id_queue);
		fclose(yyin);
		return -1;
	}

	queue_destroy(id_queue);
	fclose(yyin);

	return 0;
}

static int write_binary_policy(policydb_t * p, FILE *outfp)
{
	struct policy_file pf;

	p->policy_type = policy_type;
	p->policyvers = policyvers;
	p->handle_unknown = SEPOL_DENY_UNKNOWN;

	policy_file_init(&pf);
	pf.type = PF_USE_STDIO;
	pf.fp = outfp;
	return policydb_write(p, &pf);
}

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)
{
	sidtab_t sidtab;
	policydb_t modpolicydb;
	//policydb_t kernpolicydb;
	FILE *devnull = NULL;

	sepol_debug(0);
	sepol_set_policydb(&modpolicydb);
	sepol_set_sidtab(&sidtab);

	if (policydb_init(&modpolicydb))
		goto exit;

	modpolicydb.policy_type = POLICY_BASE;
	modpolicydb.mls = 1;
	modpolicydb.handle_unknown = DENY_UNKNOWN;
	policydb_set_target_platform(&modpolicydb, SEPOL_TARGET_SELINUX);

	if (read_source_policy(&modpolicydb, data, size))
		goto exit;

	if (hierarchy_check_constraints(NULL, &modpolicydb))
		goto exit;

	//if (policydb_init(&kernpolicydb))
	//	goto exit;

	if (link_modules(NULL, &modpolicydb, NULL, 0, 0))
		goto exit;

	//if (expand_module(NULL, &modpolicydb, &kernpolicydb, 0, 1))
	//	goto exit;

	if (policydb_load_isids(&modpolicydb, &sidtab))
		goto exit;

	sepol_sidtab_destroy(&sidtab);

	devnull = fopen("/dev/null", "w");
	if (devnull == NULL)
		goto exit;

	if (write_binary_policy(&modpolicydb, devnull))
		goto exit;

exit:
	if (devnull != NULL)
		fclose(devnull);

	//policydb_destroy(&kernpolicydb);
	policydb_destroy(&modpolicydb);

	return 0;
}

/*
 * Usage:
 *     ./checkmodule-fuzzer -only_ascii=1 -dict=fuzz-dictionary.txt -jobs=4 -workers=4 corpus_dir/
 *     tail -f fuzz-*.log | awk -e '{ print strftime("%H:%M:%S",systime()) "\t" $0}'
 *
 *     ./checkmodule-fuzzer crash-<<hash>>
 *
 *     ./checkmodule-fuzzer -merge=1 corpus_new/ corpus_dir/
 */
