//
//  sqlite_fts_init_util.c
//  FTS5Demo
//
//  Created by 徐梦华 on 2018/5/18.
//  Copyright © 2018年 Xu Menghua. All rights reserved.
//

#include "sqlite_fts_init_util.h"
#include <string.h>
#include <stdlib.h>

const char *kTurnOffSynchronousSQL = "PRAGMA synchronous = OFF;";
const char *kCreateSimpleFtsTableSQL = "CREATE VIRTUAL TABLE IF NOT EXISTS simple_fts USING fts5(DATA_ID UNINDEXED,TYPE UNINDEXED,DATA1 UNINDEXED,DATA2 UNINDEXED,DATA3 UNINDEXED,BODY,tokenize='single_word')";
const char *kCreateMutipleFtsTableSQL = "CREATE VIRTUAL TABLE IF NOT EXISTS mutiple_fts USING fts5(DATA_ID UNINDEXED,TYPE UNINDEXED,DATA1 UNINDEXED,DATA2 UNINDEXED,DATA3 UNINDEXED,BODY1,BODY2,BODY3,tokenize='single_word')";

char *sqlite_fts_init_db_path;
static sqlite3 *sqlite_fts_init_db;

void setSqliteFtsInitDbPath(const char *path) {
    sqlite_fts_init_db_path = malloc(sizeof(char)*strlen(path));
    sqlite_fts_init_db_path = strcpy(sqlite_fts_init_db_path, path);
}

const char* getSqliteFtsInitDbPath(void) {
    char *dbPath = malloc(sizeof(char)*strlen(sqlite_fts_init_db_path));
    dbPath = strcpy(dbPath, sqlite_fts_init_db_path);
    return dbPath;
}

int createTokenizer(void) {
    int result = create_single_word_tokenizer(sqlite_fts_init_db, "single_word", NULL);
    if (result != SQLITE_OK) {
        printf("sqlite error information:create tokenizer failed\n");
    }
    return result;
}

int openFtsInitDb(void) {
    int result = sqlite3_open(sqlite_fts_init_db_path, &sqlite_fts_init_db);
    return result;
}

void closeFtsInitDb(void) {
    sqlite3_close(sqlite_fts_init_db);
}

int turnOffSynchronous(void) {
    char *error = NULL;
    int result = sqlite3_exec(sqlite_fts_init_db, kTurnOffSynchronousSQL, NULL, NULL, &error);
    if (error) {
        printf("sqlite error information:%s\n", error);
    }
    return result;
}

int createSimpleFtsTable(void) {
    char *error = NULL;
    int result = sqlite3_exec(sqlite_fts_init_db, kCreateSimpleFtsTableSQL, NULL, NULL, &error);
    if (error) {
        printf("sqlite error information:%s\n", error);
    }
    return result;
}

int createMutipleFtsTable(void) {
    char *error = NULL;
    int result = sqlite3_exec(sqlite_fts_init_db, kCreateMutipleFtsTableSQL, NULL, NULL, &error);
    if (error) {
        printf("sqlite error information:%s\n", error);
    }
    return result;
}

void initFTS(const char *path) {
    setSqliteFtsInitDbPath(path);
    if (openFtsInitDb() == SQLITE_OK) {
        if (createTokenizer() == SQLITE_OK) {
            if (createSimpleFtsTable() == SQLITE_OK) {
                
            } else {
                printf("create simple fts table failed\n");
            }
            if (createMutipleFtsTable() == SQLITE_OK) {
                
            } else {
                printf("create mutiple fts table failed\n");
            }
        } else {
            printf("create tokenizer failed\n");
        }
        if (turnOffSynchronous() == SQLITE_OK) {
            printf("turn off synchronous succeed\n");
        }
    } else {
        printf("open fts init db failed\n");
    }
}

sqlite3* getSqliteFtsInitDb(void) {
    return sqlite_fts_init_db;
}
