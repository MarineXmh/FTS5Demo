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

void set_sqlite_fts_db_path(const char *path);
char* get_sqlite_fts_db_path(void);
sqlite3* get_sqlite_fts_db(void);

int open_fts_db(void);
void close_fts_db(void);
int create_tokenizer(void);
int execute_sql(const char *sql);

int create_fts_table(void);
int drop_fts_table(void);
int insert_fts(const char *type, const char *col1, const char *col2, const char *col3, const char *col4, const char *col5, const char *uCol1, const char *uCol2, const char *uCol3, const char *uCol4, const char *uCol5, const char *uCol6, const char *uCol7, const char *uCol8, const char *uCol9, const char *uCol10);
int delete_fts(const char *where);

#endif /* sqlite_fts_util_h */
