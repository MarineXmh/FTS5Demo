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
#include "sqlite_fts_single_word_tokenizer.h"

#define SQL_BUFFER_MAX_LENGTH 16384

const char *kTurnOffSynchronousSQL = "PRAGMA synchronous = OFF;";
const char *kBeginTransactionSQL = "BEGIN";
const char *kCommitTransactionSQL = "COMMIT";

const char *kCreateSimpleFtsTableSQL = "CREATE VIRTUAL TABLE IF NOT EXISTS simple_fts USING fts5(DATA_ID UNINDEXED,TYPE UNINDEXED,DATA1 UNINDEXED,DATA2 UNINDEXED,DATA3 UNINDEXED,BODY,tokenize='single_word')";
const char *kDropSimpleFtsTableSQL = "DROP TABLE simple_fts";
const char *kInsertToSimpleFtsTableSQL = "INSERT INTO simple_fts VALUES ('%s','%s','%s','%s','%s','%s')";
const char *kInsertToSimpleFtsTableBindSQL = "INSERT INTO simple_fts VALUES (?,?,?,?,?,?)";
const char *kDeleteFromSimpleFtsTableByIdSQL = "DELETE FROM simple_fts WHERE DATA_ID='%s'";
const char *kDeleteFromSimpleFtsTableByIdBindSQL = "DELETE FROM simple_fts WHERE DATA_ID=?";
const char *kUpdateSimpleFtsTableByIdSQL = "UPDATE simple_fts SET DATA_ID='%s',TYPE='%s',DATA1='%s',DATA2='%s',DATA3='%s',BODY='%s' WHERE DATA_ID='%s'";
const char *kUpdateSimpleFtsTableByIdBindSQL = "UPDATE simple_fts SET DATA_ID=?,TYPE=?,DATA1=?,DATA2=?,DATA3=?,BODY=? WHERE DATA_ID=?";

const char *kCreateMutipleFtsTableSQL = "CREATE VIRTUAL TABLE IF NOT EXISTS mutiple_fts USING fts5(DATA_ID UNINDEXED,TYPE UNINDEXED,DATA1 UNINDEXED,DATA2 UNINDEXED,DATA3 UNINDEXED,BODY1,BODY2,BODY3,tokenize='single_word')";
const char *kDropMutipleFtsTableSQL = "DROP TABLE mutiple_fts";
const char *kInsertToMutipleFtsTableSQL = "INSERT INTO mutiple_fts VALUES ('%s','%s','%s','%s','%s','%s','%s','%s')";
const char *kInsertToMutipleFtsTableBindSQL = "INSERT INTO mutiple_fts VALUES (?,?,?,?,?,?,?,?)";
const char *kDeleteFromMutipleFtsTableByIdSQL = "DELETE FROM mutiple_fts WHERE DATA_ID='%s'";
const char *kDeleteFromMutipleFtsTableByIdBindSQL = "DELETE FROM mutiple_fts WHERE DATA_ID=?";
const char *kUpdateMutipleFtsTableByIdSQL = "UPDATE mutiple_fts SET DATA_ID='%s',TYPE='%s',DATA1='%s',DATA2='%s',DATA3='%s',BODY1='%s',BODY2='%s',BODY3='%s' WHERE DATA_ID='%s'";
const char *kUpdateMutipleFtsTableByIdBindSQL = "UPDATE mutiple_fts SET DATA_ID=?,TYPE=?,DATA1=?,DATA2=?,DATA3=?,BODY1=?,BODY2=?,BODY3=? WHERE DATA_ID=?";

char *sqlite_fts_db_path;
static sqlite3 *sqlite_fts_db;

void setSqliteFtsDbPath(const char *path) {
    sqlite_fts_db_path = malloc(sizeof(char)*strlen(path));
    sqlite_fts_db_path = strcpy(sqlite_fts_db_path, path);
}

char* getSqliteFtsDbPath(void) {
    return sqlite_fts_db_path;
}

sqlite3* getSqliteFtsDb(void) {
    return sqlite_fts_db;
}

void logErrorInformation(char *error) {
    printf("sqlite error information:%s\n", error);
}

int openFtsDb(void) {
    int result = sqlite3_open(sqlite_fts_db_path, &sqlite_fts_db);
    return result;
}

void closeFtsDb(void) {
    sqlite3_close(sqlite_fts_db);
}

int createTokenizer(void) {
    int result = create_single_word_tokenizer(sqlite_fts_db, "single_word", NULL);
    if (result != SQLITE_OK) {
        printf("create tokenizer failed\n");
    }
    return result;
}

int executeSql(const char *sql) {
    char *error = NULL;
    int result = sqlite3_exec(sqlite_fts_db, sql, NULL, NULL, &error);
    if (error) {
        logErrorInformation(error);
    }
    return result;
}

int turnOffSynchronous(void) {
    return executeSql(kTurnOffSynchronousSQL);
}

int beginTransaction(void) {
    return executeSql(kBeginTransactionSQL);
}

int commitTransaction(void) {
    return executeSql(kCommitTransactionSQL);
}

int createSimpleFtsTable(void) {
    char *error = NULL;
    int result = sqlite3_exec(sqlite_fts_db, kCreateSimpleFtsTableSQL, NULL, NULL, &error);
    if (error) {
        logErrorInformation(error);
    }
    return result;
}

int dropSimpleFtsTable(void) {
    char *error = NULL;
    int result = sqlite3_exec(sqlite_fts_db, kDropSimpleFtsTableSQL, NULL, NULL, &error);
    if (error) {
        logErrorInformation(error);
    }
    return result;
}

int insertDataToSimpleFts(const char *data_id, const char *type, const char *data1, const char *data2, const char *data3, const char *body) {
    char sql[SQL_BUFFER_MAX_LENGTH];
    sprintf(sql, kInsertToSimpleFtsTableSQL,data_id, type, data1, data2, data3, body);
    char *error = NULL;
    int result = sqlite3_exec(sqlite_fts_db, sql, NULL, NULL, &error);
    if (error) {
        logErrorInformation(error);
    }
    return result;
}

int deleteFromSimpleFtsById(const char *data_id) {
    char sql[SQL_BUFFER_MAX_LENGTH];
    sprintf(sql, kDeleteFromSimpleFtsTableByIdSQL, data_id);
    char *error = NULL;
    int result = sqlite3_exec(sqlite_fts_db, sql, NULL, NULL, &error);
    if (error) {
        logErrorInformation(error);
    }
    return result;
}

int updateSimpleFtsByid(const char *data_id, const char *type, const char *data1, const char *data2, const char *data3, const char *body) {
    char sql[SQL_BUFFER_MAX_LENGTH];
    sprintf(sql, kUpdateSimpleFtsTableByIdSQL, data_id, type, data1, data2, data3, body, data_id);
    char *error = NULL;
    int result = sqlite3_exec(sqlite_fts_db, sql, NULL, NULL, &error);
    if (error) {
        logErrorInformation(error);
    }
    return result;
}

int createMutipleFtsTable(void) {
    char *error = NULL;
    int result = sqlite3_exec(sqlite_fts_db, kCreateMutipleFtsTableSQL, NULL, NULL, &error);
    if (error) {
        logErrorInformation(error);
    }
    return result;
}

int dropMutipleFtsTable(void) {
    char *error = NULL;
    int result = sqlite3_exec(sqlite_fts_db, kDropMutipleFtsTableSQL, NULL, NULL, &error);
    if (error) {
        logErrorInformation(error);
    }
    return result;
}

int insertDataToMutipleFts(const char *data_id, const char *type, const char *data1, const char *data2, const char *data3, const char *body1, const char *body2, const char *body3) {
    char sql[SQL_BUFFER_MAX_LENGTH];
    sprintf(sql, kInsertToMutipleFtsTableSQL,data_id, type, data1, data2, data3, body1, body2, body3);
    char *error = NULL;
    int result = sqlite3_exec(sqlite_fts_db, sql, NULL, NULL, &error);
    if (error) {
        logErrorInformation(error);
    }
    return result;
}

int deleteFromMutipleFtsById(const char *data_id) {
    char sql[SQL_BUFFER_MAX_LENGTH];
    sprintf(sql, kDeleteFromMutipleFtsTableByIdSQL, data_id);
    char *error = NULL;
    int result = sqlite3_exec(sqlite_fts_db, sql, NULL, NULL, &error);
    if (error) {
        logErrorInformation(error);
    }
    return result;
}

int updateMutipleFtsByid(const char *data_id, const char *type, const char *data1, const char *data2, const char *data3, const char *body1, const char *body2, const char *body3) {
    char sql[SQL_BUFFER_MAX_LENGTH];
    sprintf(sql, kUpdateMutipleFtsTableByIdSQL, data_id, type, data1, data2, data3, body1, body2, body3, data_id);
    char *error = NULL;
    int result = sqlite3_exec(sqlite_fts_db, sql, NULL, NULL, &error);
    if (error) {
        logErrorInformation(error);
    }
    return result;
}
