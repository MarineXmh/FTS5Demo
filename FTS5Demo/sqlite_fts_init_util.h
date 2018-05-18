//
//  sqlite_fts_init_util.h
//  FTS5Demo
//
//  Created by 徐梦华 on 2018/5/18.
//  Copyright © 2018年 Xu Menghua. All rights reserved.
//

#ifndef SQLITE3_H
#include "sqlite3.h"
#endif

#ifndef sqlite_fts_init_util_h
#define sqlite_fts_init_util_h

#include <stdio.h>
#include "sqlite_fts_single_word_tokenizer.h"

extern const char *kCreateSimpleFtsTableSQL;
extern const char *kCreateMutipleFtsTableSQL;
extern const char *kTurnOffSynchronousSQL;

void setSqliteFtsInitDbPath(const char *path);
const char* getSqliteFtsInitDbPath(void);
int openFtsInitDb(void);
void closeFtsInitDb(void);
int turnOffSynchronous(void);
int createTokenizer(void);
int createSimpleFtsTable(void);
int dropSimpleFtsTable(void);
int createMutipleFtsTable(void);
int dropMutipleFtsTable(void);
void initFTS(const char *path);
sqlite3* getSqliteFtsInitDb(void);

#endif /* sqlite_fts_init_util_h */
