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

// feed_table
int create_feed_table(void) {
    const char *sql = "create virtual table if not exists feed_fts using fts5(feed_id unindexed,title,pin_yin,pin_yin_for_short,tokenize='single_word')";
    char *error = NULL;
    int result = sqlite3_exec(sqlite_fts_db, sql, NULL, NULL, &error);
    if (error) {
        log_error_information(error);
    }
    return result;
}

int drop_feed_table(void) {
    const char *sql = "drop table feed_fts";
    char *error = NULL;
    int result = sqlite3_exec(sqlite_fts_db, sql, NULL, NULL, &error);
    if (error) {
        log_error_information(error);
    }
    return result;
}

int insert_feed(const char *feed_id, const char *title, const char *pin_yin, const char *pin_yin_for_short) {
    const char *insert = "insert into feed_fts values ('%s','%s','%s','%s')";
    char sql[SQL_BUFFER_MAX_LENGTH];
    sprintf(sql, insert, feed_id, title, pin_yin, pin_yin_for_short);
    char *error = NULL;
    int result = sqlite3_exec(sqlite_fts_db, sql, NULL, NULL, &error);
    if (error) {
        log_error_information(error);
    }
    return result;
}

int delete_feed(const char *where) {
    const char *delete = "delete from feed_fts where %s";
    char sql[SQL_BUFFER_MAX_LENGTH];
    sprintf(sql, delete, where);
    char *error = NULL;
    int result = sqlite3_exec(sqlite_fts_db, sql, NULL, NULL, &error);
    if (error) {
        log_error_information(error);
    }
    return result;
}

int update_feed(const char *set, const char *where) {
    const char *update = "update feed_fts set %s where %s";
    char sql[SQL_BUFFER_MAX_LENGTH];
    sprintf(sql, update, set, where);
    char *error = NULL;
    int result = sqlite3_exec(sqlite_fts_db, sql, NULL, NULL, &error);
    if (error) {
        log_error_information(error);
    }
    return result;
}
// feed_table

// message_table
int create_message_table(void) {
    const char *sql = "create virtual table if not exists message_fts using fts5(id unindexed,message,tokenize='single_word')";
    char *error = NULL;
    int result = sqlite3_exec(sqlite_fts_db, sql, NULL, NULL, &error);
    if (error) {
        log_error_information(error);
    }
    return result;
}

int drop_message_table(void) {
    const char *sql = "drop table message_fts";
    char *error = NULL;
    int result = sqlite3_exec(sqlite_fts_db, sql, NULL, NULL, &error);
    if (error) {
        log_error_information(error);
    }
    return result;
}

int insert_message(const char *id, const char *message) {
    const char *insert = "insert into message_fts values ('%s','%s')";
    char sql[SQL_BUFFER_MAX_LENGTH];
    sprintf(sql, insert, id, message);
    char *error = NULL;
    int result = sqlite3_exec(sqlite_fts_db, sql, NULL, NULL, &error);
    if (error) {
        log_error_information(error);
    }
    return result;
}

int delete_message(const char *where) {
    char *delete = "delete from message_fts where %s";
    char sql[SQL_BUFFER_MAX_LENGTH];
    sprintf(sql, delete, where);
    char *error = NULL;
    int result = sqlite3_exec(sqlite_fts_db, sql, NULL, NULL, &error);
    if (error) {
        log_error_information(error);
    }
    return result;
}

int update_message(const char *set, const char *where) {
    const char *update = "update message_fts set %s where %s";
    char sql[SQL_BUFFER_MAX_LENGTH];
    sprintf(sql, update, set, where);
    char *error = NULL;
    int result = sqlite3_exec(sqlite_fts_db, sql, NULL, NULL, &error);
    if (error) {
        log_error_information(error);
    }
    return result;
}

// message_table
