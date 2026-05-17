/*
 * SQLite bridge for Quartus in Rosetta-based environments.
 *
 * Build:
 *   gcc -shared -fPIC -O2 -Wall -Wextra -o libccl_sqlite3.so altr_sqlite_bridge.c -ldl
 */

#include <dlfcn.h>
#include <sqlite3.h>
#include <stdio.h>
#include <stdlib.h>

static void *handle = NULL;

static void *get_func(const char *name) {
  if (!handle) {
    handle = dlopen("/usr/lib/x86_64-linux-gnu/libsqlite3.so.0", RTLD_NOW | RTLD_GLOBAL);
    if (!handle) {
      fprintf(stderr, "Bridge Error: %s\n", dlerror());
      exit(1);
    }
  }
  return dlsym(handle, name);
}

/* Rosetta AVX compatibility shim */
int hasHighPrecisionDouble(void) { return 1; }

int altr_sqlite3_initialize(void) { return ((int (*)(void))get_func("sqlite3_initialize"))(); }
int altr_sqlite3_shutdown(void) { return 0; }
int altr_sqlite3_config(int i, ...) {
  (void)i;
  return 0;
}

int altr_sqlite3_open_v2(const char *f, sqlite3 **db, int fl, const char *v) {
  return ((int (*)(const char *, sqlite3 **, int, const char *))get_func("sqlite3_open_v2"))(f, db, fl, v);
}
int altr_sqlite3_close(sqlite3 *db) { return ((int (*)(sqlite3 *))get_func("sqlite3_close"))(db); }
int altr_sqlite3_exec(sqlite3 *db, const char *s, int (*c)(void *, int, char **, char **), void *a, char **e) {
  return ((int (*)(sqlite3 *, const char *, int (*)(void *, int, char **, char **), void *, char **))get_func("sqlite3_exec"))(
      db, s, c, a, e);
}

int altr_sqlite3_prepare_v2(sqlite3 *db, const char *z, int n, sqlite3_stmt **s, const char **p) {
  return ((int (*)(sqlite3 *, const char *, int, sqlite3_stmt **, const char **))get_func("sqlite3_prepare_v2"))(db, z, n,
                                                                                                                   s, p);
}
int altr_sqlite3_step(sqlite3_stmt *s) { return ((int (*)(sqlite3_stmt *))get_func("sqlite3_step"))(s); }
int altr_sqlite3_finalize(sqlite3_stmt *s) { return ((int (*)(sqlite3_stmt *))get_func("sqlite3_finalize"))(s); }
int altr_sqlite3_reset(sqlite3_stmt *s) { return ((int (*)(sqlite3_stmt *))get_func("sqlite3_reset"))(s); }

int altr_sqlite3_bind_int(sqlite3_stmt *s, int i, int v) {
  return ((int (*)(sqlite3_stmt *, int, int))get_func("sqlite3_bind_int"))(s, i, v);
}
int altr_sqlite3_bind_null(sqlite3_stmt *s, int i) {
  return ((int (*)(sqlite3_stmt *, int))get_func("sqlite3_bind_null"))(s, i);
}
int altr_sqlite3_bind_double(sqlite3_stmt *s, int i, double v) {
  return ((int (*)(sqlite3_stmt *, int, double))get_func("sqlite3_bind_double"))(s, i, v);
}
int altr_sqlite3_bind_text(sqlite3_stmt *s, int i, const char *v, int n, void (*d)(void *)) {
  return ((int (*)(sqlite3_stmt *, int, const char *, int, void (*)(void *)))get_func("sqlite3_bind_text"))(s, i, v, n, d);
}
int altr_sqlite3_bind_blob(sqlite3_stmt *s, int i, const void *v, int n, void (*d)(void *)) {
  return ((int (*)(sqlite3_stmt *, int, const void *, int, void (*)(void *)))get_func("sqlite3_bind_blob"))(s, i, v, n, d);
}

int altr_sqlite3_column_int(sqlite3_stmt *s, int i) {
  return ((int (*)(sqlite3_stmt *, int))get_func("sqlite3_column_int"))(s, i);
}
long long altr_sqlite3_column_int64(sqlite3_stmt *s, int i) {
  return ((long long (*)(sqlite3_stmt *, int))get_func("sqlite3_column_int64"))(s, i);
}
double altr_sqlite3_column_double(sqlite3_stmt *s, int i) {
  return ((double (*)(sqlite3_stmt *, int))get_func("sqlite3_column_double"))(s, i);
}
const char *altr_sqlite3_column_text(sqlite3_stmt *s, int i) {
  return ((const char *(*)(sqlite3_stmt *, int))get_func("sqlite3_column_text"))(s, i);
}
const char *altr_sqlite3_column_decltype(sqlite3_stmt *s, int i) {
  return ((const char *(*)(sqlite3_stmt *, int))get_func("sqlite3_column_decltype"))(s, i);
}
int altr_sqlite3_column_type(sqlite3_stmt *s, int i) {
  return ((int (*)(sqlite3_stmt *, int))get_func("sqlite3_column_type"))(s, i);
}
int altr_sqlite3_column_count(sqlite3_stmt *s) { return ((int (*)(sqlite3_stmt *))get_func("sqlite3_column_count"))(s); }
int altr_sqlite3_column_bytes(sqlite3_stmt *s, int i) {
  return ((int (*)(sqlite3_stmt *, int))get_func("sqlite3_column_bytes"))(s, i);
}
const void *altr_sqlite3_column_blob(sqlite3_stmt *s, int i) {
  return ((const void *(*)(sqlite3_stmt *, int))get_func("sqlite3_column_blob"))(s, i);
}
const char *altr_sqlite3_column_name(sqlite3_stmt *s, int i) {
  return ((const char *(*)(sqlite3_stmt *, int))get_func("sqlite3_column_name"))(s, i);
}

int altr_sqlite3_errcode(sqlite3 *db) { return ((int (*)(sqlite3 *))get_func("sqlite3_errcode"))(db); }
const char *altr_sqlite3_errmsg(sqlite3 *db) { return ((const char *(*)(sqlite3 *))get_func("sqlite3_errmsg"))(db); }
int altr_sqlite3_changes(sqlite3 *db) { return ((int (*)(sqlite3 *))get_func("sqlite3_changes"))(db); }
long long altr_sqlite3_last_insert_rowid(sqlite3 *db) {
  return ((long long (*)(sqlite3 *))get_func("sqlite3_last_insert_rowid"))(db);
}

