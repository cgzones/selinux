/*
 * Copyright (C) 2006 Tresys Technology, LLC
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2.1 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */

/* Copyright (C) 2005 Red Hat, Inc. */

#include <threads.h>

struct semanage_bool;
struct semanage_bool_key;
typedef struct semanage_bool record_t;
typedef struct semanage_bool_key record_key_t;
#define DBASE_RECORD_DEFINED

struct dbase_policydb;
typedef struct dbase_policydb dbase_t;
#define DBASE_DEFINED

#include <sepol/booleans.h>
#include <semanage/handle.h>
#include "boolean_internal.h"
#include "debug.h"
#include "database_policydb.h"
#include "semanage_store.h"

static int sepol_bool_set_wrapper(sepol_handle_t * handle,
				  sepol_policydb_t * policydb,
				  const record_key_t * key,
				  const record_t * data)
{
	return sepol_bool_set(handle, policydb, (const sepol_bool_key_t *)key, (const sepol_bool_t *)data);
}

static int sepol_bool_exists_wrapper(sepol_handle_t * handle,
			     	     const sepol_policydb_t * policydb,
			   	     const record_key_t * key,
				     int *response)
{
	return sepol_bool_exists(handle, policydb, (const sepol_bool_key_t *)key, response);
}

static int sepol_bool_query_wrapper(sepol_handle_t * handle,
			    	    const sepol_policydb_t * p,
			   	    const record_key_t * key,
			 	    record_t ** response)
{
	return sepol_bool_query(handle, p, (const sepol_bool_key_t *)key, (sepol_bool_t **)response);
}

static thread_local int (*saved_fn) (const record_t * boolean, void *fn_arg) = NULL;

static int callback_wrapper(const sepol_bool_t *boolean, void *arg) {
	return saved_fn((const record_t *)boolean, arg);
}

static int sepol_bool_iterate_wrapper(sepol_handle_t * handle,
				      const sepol_policydb_t * policydb,
			  	      int (*fn) (const record_t * boolean, void *fn_arg),
				      void *arg)
{
	saved_fn = fn;

	return sepol_bool_iterate(handle, policydb, callback_wrapper, arg);
}

/* BOOLEAN RECRORD (SEPOL): POLICYDB extension: method table */
static const record_policydb_table_t SEMANAGE_BOOL_POLICYDB_RTABLE = {
	.add = NULL,
	.modify = NULL,
	.set = sepol_bool_set_wrapper,
	.query = sepol_bool_query_wrapper,
	.count = sepol_bool_count,
	.exists = sepol_bool_exists_wrapper,
	.iterate = sepol_bool_iterate_wrapper,
};

int bool_policydb_dbase_init(semanage_handle_t * handle,
			     dbase_config_t * dconfig)
{

	if (dbase_policydb_init(handle,
				semanage_path(SEMANAGE_ACTIVE, SEMANAGE_STORE_KERNEL),
				semanage_path(SEMANAGE_TMP, SEMANAGE_STORE_KERNEL),
				&SEMANAGE_BOOL_RTABLE,
				&SEMANAGE_BOOL_POLICYDB_RTABLE,
				&dconfig->dbase) < 0)
		return STATUS_ERR;

	dconfig->dtable = &SEMANAGE_POLICYDB_DTABLE;
	return STATUS_SUCCESS;
}

void bool_policydb_dbase_release(dbase_config_t * dconfig)
{

	dbase_policydb_release(dconfig->dbase);
}
