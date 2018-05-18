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

extern const char *kBeginTransactionSQL;
extern const char *kCommitTransactionSQL;

extern const char *kDropSimpleFtsTableSQL;
extern const char *kInsertToSimpleFtsTableSQL;
extern const char *kInsertToSimpleFtsTableBindSQL;
extern const char *kDeleteFromSimpleFtsTableByIdSQL;
extern const char *kDeleteFromSimpleFtsTableByIdBindSQL;
extern const char *kUpdateSimpleFtsTableByIdSQL;
extern const char *kUpdateSimpleFtsTableByIdBindSQL;

extern const char *kDropMutipleFtsTableSQL;
extern const char *kInsertToMutipleFtsTableSQL;
extern const char *kInsertToMutipleFtsTableBindSQL;
extern const char *kDeleteFromMutipleFtsTableByIdSQL;
extern const char *kDeleteFromMutipleFtsTableByIdBindSQL;
extern const char *kUpdateMutipleFtsTableByIdSQL;
extern const char *kUpdateMutipleFtsTableByIdBindSQL;

void setSqliteFtsUtilDb(sqlite3 *db);
sqlite3* getSqliteFtsUtilDb(void);

int executeSql(const char *sql);

int beginTransaction(void);
int commitTransaction(void);

int insertDataToSimpleFts(const char *data_id, const char *type, const char *data1, const char *data2, const char *data3, const char *body);
int deleteFromSimpleFtsById(const char *data_id);
int updateSimpleFtsByid(const char *data_id, const char *type, const char *data1, const char *data2, const char *data3, const char *body);

int insertDataToMutipleFts(const char *data_id, const char *type, const char *data1, const char *data2, const char *data3, const char *body1, const char *body2, const char *body3);
int deleteFromMutipleFtsById(const char *data_id);
int updateMutipleFtsById(const char *data_id, const char *type, const char *data1, const char *data2, const char *data3, const char *body1, const char *body2, const char *body3);

#endif /* sqlite_fts_util_h */
