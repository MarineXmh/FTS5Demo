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

// feed_table
int create_feed_table(void);
int drop_feed_table(void);
int insert_feed(const char *feed_id, const char *title, const char *pin_yin, const char *pin_yin_for_short);
int delete_feed(const char *where);
int update_feed(const char *set, const char *where);
//

// message_table
int create_message_table(void);
int drop_message_table(void);
int insert_message(const char *id, const char *message);
int delete_message(const char *where);
int update_message(const char *set, const char *where);
//

#endif /* sqlite_fts_util_h */
