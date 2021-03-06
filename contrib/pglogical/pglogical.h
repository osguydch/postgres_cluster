/*-------------------------------------------------------------------------
 *
 * pglogical.h
 *              pglogical replication plugin
 *
 * Copyright (c) 2015, PostgreSQL Global Development Group
 *
 * IDENTIFICATION
 *              pglogical.h
 *
 *-------------------------------------------------------------------------
 */
#ifndef PGLOGICAL_H
#define PGLOGICAL_H

#include "storage/s_lock.h"
#include "postmaster/bgworker.h"
#include "utils/array.h"

#include "libpq-fe.h"

#include "pglogical_fe.h"
#include "pglogical_node.h"

#define PGLOGICAL_VERSION "1.0.1"
#define PGLOGICAL_VERSION_NUM 10001

#define PGLOGICAL_MIN_PROTO_VERSION_NUM 1
#define PGLOGICAL_MAX_PROTO_VERSION_NUM 1

#define EXTENSION_NAME "pglogical"

#define PGLOGICAL_MASTER_TOC_MAGIC	123
#define PGLOGICAL_MASTER_TOC_STATE	1
#define PGLOGICAL_MASTER_TOC_APPLY	2

#define REPLICATION_ORIGIN_ALL "all"

extern bool pglogical_synchronous_commit;
extern char *pglogical_temp_directory;

extern char *shorten_hash(const char *str, int maxlen);

extern List *textarray_to_list(ArrayType *textarray);

extern Oid get_pglogical_table_oid(const char *table);

extern void pglogical_execute_sql_command(char *cmdstr, char *role,
										  bool isTopLevel);

extern PGconn *pglogical_connect(const char *connstring, const char *connname);
extern PGconn *pglogical_connect_replica(const char *connstring,
										 const char *connname);
extern void pglogical_start_replication(PGconn *streamConn,
										const char *slot_name,
										XLogRecPtr start_pos,
										const char *forward_origins,
										const char *replication_sets,
										const char *replicate_only_table);

extern void apply_work(PGconn *streamConn);

#endif /* PGLOGICAL_H */
