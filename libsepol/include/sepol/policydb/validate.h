#ifndef _SEPOL_POLICYDB_VALIDATE_H
#define _SEPOL_POLICYDB_VALIDATE_H

#include <sepol/handle.h>
#include <sepol/policydb/policydb.h>

#ifdef __cplusplus
extern "C" {
#endif

int policydb_validate(sepol_handle_t *handle, const policydb_t *p);

#ifdef __cplusplus
}
#endif

#endif
