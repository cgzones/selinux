#include <stdlib.h>

#include <sepol/policydb/policydb.h>

int sepol_kernel_policydb_to_conf(FILE *out, struct policydb *pdb);
