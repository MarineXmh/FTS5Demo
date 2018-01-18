//
//  SqliteFTSUtil.m
//  FTS5Demo
//
//  Created by Xu Menghua on 2018/1/4.
//  Copyright © 2018年 Xu Menghua. All rights reserved.
//

#import "SqliteFTSUtil.h"
#import "sqlite_fts_util.h"

@interface SqliteFTSUtil ()



@end

@implementation SqliteFTSUtil

+ (NSMutableArray *)selectWithTable:(NSString *)table Column:(NSString *)column Match:(NSString *)match {
    NSMutableArray *array = [[NSMutableArray alloc] init];
    if (table == nil || [table isEqualToString:@""]) {
        return array;
    }
    if (column == nil || [column isEqualToString:@""]) {
        column = table;
    }
    if (match == nil || [match isEqualToString:@""]) {
        match = @"*";
    }
    sqlite3 *db = get_sqlite_fts_db();
    NSString *sqlite = [NSString stringWithFormat:@"select * from %@ where %@ match '%@'", table, column, match];
    sqlite3_stmt *stmt = NULL;
    int result = sqlite3_prepare_v2(db, sqlite.UTF8String, -1, &stmt, NULL);
    if (result == SQLITE_OK) {
        int columnCount = sqlite3_column_count(stmt);
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            NSMutableDictionary *data = [NSMutableDictionary dictionary];
            for (int i = 0; i < columnCount; i++) {
                NSString *text = [NSString stringWithUTF8String:(const char *)sqlite3_column_text(stmt, i)];
                NSString *column = [NSString stringWithUTF8String:(const char *)sqlite3_column_name(stmt, i)];
                [data setObject:text forKey:column];
            }
            [array addObject:data];
        }
    } else {
        const char* error = sqlite3_errmsg(db);
        NSLog(@"查询失败:%s", error);
    }
    sqlite3_finalize(stmt);
    return array;
}

+ (int)executeWithSql:(NSString *)sql {
    if (sql == nil || [sql isEqualToString:@""]) {
        return SQLITE_ERROR;
    }
    sqlite3 *db = get_sqlite_fts_db();
    char *error = NULL;
    int result = sqlite3_exec(db, [sql UTF8String], nil, nil, &error);
    return result;
}

+ (int)insertArrayToFeed:(NSArray *)array {
    for (NSDictionary *data in array) {
        NSString *feedId = [data objectForKey:@"feedId"];
        const char *feed_id = [feedId cStringUsingEncoding:NSUTF8StringEncoding];
        NSString *titleString = [data objectForKey:@"title"];
        const char *title = [titleString cStringUsingEncoding:NSUTF8StringEncoding];
        NSString *pinYin = [data objectForKey:@"pinYin"];
        const char *pin_yin = [pinYin cStringUsingEncoding:NSUTF8StringEncoding];
        NSString *pinYinForShort = [data objectForKey:@"pinYinForShort"];
        const char *pin_yin_for_short = [pinYinForShort cStringUsingEncoding:NSUTF8StringEncoding];
        int result = insert_feed(feed_id, title, pin_yin, pin_yin_for_short);
        if (result != SQLITE_OK) {
            return result;
        }
    }
    return SQLITE_OK;
}

+ (int)insertArrayToMessage:(NSArray *)array {
    for (NSDictionary *data in array) {
        NSString *idString = [data objectForKey:@"id"];
        const char *id = [idString cStringUsingEncoding:NSUTF8StringEncoding];
        NSString *messageString = [data objectForKey:@"message"];
        const char *message = [messageString cStringUsingEncoding:NSUTF8StringEncoding];
        int result = insert_message(id, message);
        if (result != SQLITE_OK) {
            return result;
        }
    }
    return SQLITE_OK;
}

@end
