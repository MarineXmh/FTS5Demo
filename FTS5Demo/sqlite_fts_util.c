//
//  sqlite_fts_util.c
//  FTS5Demo
//
//  Created by Xu Menghua on 2018/1/3.
//  Copyright © 2018年 Xu Menghua. All rights reserved.
//

#include "sqlite_fts_util.h"
#include <string.h>
#include <stdlib.h>
#include "sqlite_fts_single_word_icu_tokenizer.h"

#define SQL_BUFFER_MAX_LENGTH 16384

const char *kTurnOffSynchronous = "PRAGMA synchronous = OFF;";
const char *kCreateFtsTable = "create virtual table if not exists fts using fts5(type unindexed,col1,col2,col3,col4,col5,uCol1 unindexed,uCol2 unindexed,uCol3 unindexed,uCol4 unindexed,uCol5 unindexed,uCol6 unindexed,uCol7 unindexed,uCol8 unindexed,uCol9 unindexed,uCol10 unindexed,tokenize='single_word')";
const char *kDropFtsTable = "drop table fts";
const char *kInsertToFtsTable = "insert into fts values ('%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s')";
const char *kInsertToFtsTableBind = "insert into fts values (?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?)";
const char *kDeleteFromFtsTable = "delete from fts where %s";
const char *kUpdateFtsTable = "update fts set %s where %s";
const char *kBeginTransaction = "begin";
const char *kCommitTransaction = "commit";

char *sqlite_fts_db_path;
static sqlite3 *sqlite_fts_db;

void set_sqlite_fts_db_path(const char *path) {
    sqlite_fts_db_path = malloc(sizeof(char)*strlen(path));
    sqlite_fts_db_path = strcpy(sqlite_fts_db_path, path);
}

char* get_sqlite_fts_db_path(void) {
    return sqlite_fts_db_path;
}

sqlite3* get_sqlite_fts_db(void) {
    return sqlite_fts_db;
}

void log_error_information(char *error) {
    printf("sqlite error information:%s\n", error);
}

int open_fts_db(void) {
    int result = sqlite3_open(sqlite_fts_db_path, &sqlite_fts_db);
    return result;
}

void close_fts_db(void) {
    sqlite3_close(sqlite_fts_db);
}

int create_tokenizer(void) {
    int result = create_single_word_tokenizer(sqlite_fts_db, "single_word", NULL);
    if (result != SQLITE_OK) {
        printf("create tokenizer failed");
    }
    return result;
}

int execute_sql(const char *sql) {
    char *error = NULL;
    int result = sqlite3_exec(sqlite_fts_db, sql, NULL, NULL, &error);
    if (error) {
        log_error_information(error);
    }
    return result;
}

int turnOffSynchronous(void) {
    return execute_sql(kTurnOffSynchronous);
}

int beginTransaction(void) {
    return execute_sql(kBeginTransaction);
}

int commitTransaction(void) {
    return execute_sql(kCommitTransaction);
}

int create_fts_table(void) {
    char *error = NULL;
    int result = sqlite3_exec(sqlite_fts_db, kCreateFtsTable, NULL, NULL, &error);
    if (error) {
        log_error_information(error);
    }
    return result;
}

int drop_fts_table(void) {
    char *error = NULL;
    int result = sqlite3_exec(sqlite_fts_db, kDropFtsTable, NULL, NULL, &error);
    if (error) {
        log_error_information(error);
    }
    return result;
}

int insert_fts(const char *type, const char *col1, const char *col2, const char *col3, const char *col4, const char *col5, const char *uCol1, const char *uCol2, const char *uCol3, const char *uCol4, const char *uCol5, const char *uCol6, const char *uCol7, const char *uCol8, const char *uCol9, const char *uCol10) {
    char sql[SQL_BUFFER_MAX_LENGTH];
    sprintf(sql, kInsertToFtsTable, type, col1, col2, col3, col4, col5, uCol1, uCol2, uCol3, uCol4, uCol5, uCol6, uCol7, uCol8, uCol9, uCol10);
    char *error = NULL;
    int result = sqlite3_exec(sqlite_fts_db, sql, NULL, NULL, &error);
    if (error) {
        log_error_information(error);
    }
    return result;
}

int delete_fts(const char *where) {
    char sql[SQL_BUFFER_MAX_LENGTH];
    sprintf(sql, kDeleteFromFtsTable, where);
    char *error = NULL;
    int result = sqlite3_exec(sqlite_fts_db, sql, NULL, NULL, &error);
    if (error) {
        log_error_information(error);
    }
    return result;
}

int update_fts(const char *set, const char *where) {
    char sql[SQL_BUFFER_MAX_LENGTH];
    sprintf(sql, kUpdateFtsTable, set, where);
    char *error = NULL;
    int result = sqlite3_exec(sqlite_fts_db, sql, NULL, NULL, &error);
    if (error) {
        log_error_information(error);
    }
    return result;
}

// message_table
