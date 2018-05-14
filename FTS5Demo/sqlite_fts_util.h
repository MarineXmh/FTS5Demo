//
//  sqlite_fts_util.h
//  FTS5Demo
//
//  Created by Xu Menghua on 2018/1/3.
//  Copyright © 2018年 Xu Menghua. All rights reserved.
//

#ifndef SQLITE3_H
#include "sqlite3.h"
#endif

#ifndef sqlite_fts_util_h
#define sqlite_fts_util_h

#include <stdio.h>

extern const char *kTurnOffSynchronousSQL;
extern const char *kBeginTransactionSQL;
extern const char *kCommitTransactionSQL;

extern const char *kCreateSimpleFtsTableSQL;
extern const char *kDropSimpleFtsTableSQL;
extern const char *kInsertToSimpleFtsTableSQL;
extern const char *kInsertToSimpleFtsTableBindSQL;
extern const char *kDeleteFromSimpleFtsTableByIdSQL;
extern const char *kDeleteFromSimpleFtsTableByIdBindSQL;
extern const char *kUpdateSimpleFtsTableByIdSQL;
extern const char *kUpdateSimpleFtsTableByIdBindSQL;

extern const char *kCreateMutipleFtsTableSQL;
extern const char *kDropMutipleFtsTableSQL;
extern const char *kInsertToMutipleFtsTableSQL;
extern const char *kInsertToMutipleFtsTableBindSQL;
extern const char *kDeleteFromMutipleFtsTableByIdSQL;
extern const char *kDeleteFromMutipleFtsTableByIdBindSQL;
extern const char *kUpdateMutipleFtsTableByIdSQL;
extern const char *kUpdateMutipleFtsTableByIdBindSQL;

void setSqliteFtsDbPath(const char *path);
char* getSqliteFtsDbPath(void);
sqlite3* getSqliteFtsDb(void);

int openFtsDb(void);
void closeFtsDb(void);
int createTokenizer(void);
int executeSql(const char *sql);

int beginTransaction(void);
int commitTransaction(void);
int turnOffSynchronous(void);

int createSimpleFtsTable(void);
int dropSimpleFtsTable(void);
int insertDataToSimpleFts(const char *data_id, const char *type, const char *data1, const char *data2, const char *data3, const char *body);
int deleteFromSimpleFtsById(const char *data_id);

int createMutipleFtsTable(void);
int dropMutipleFtsTable(void);
int insertDataToMutipleFts(const char *data_id, const char *type, const char *data1, const char *data2, const char *data3, const char *body1, const char *body2, const char *body3);
int deleteFromMutipleFtsById(const char *data_id);
int updateMutipleFtsByid(const char *data_id, const char *type, const char *data1, const char *data2, const char *data3, const char *body1, const char *body2, const char *body3);

#endif /* sqlite_fts_util_h */
