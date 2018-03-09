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
    NSDate *startTime = [NSDate date];
    int result = sqlite3_prepare_v2(db, sqlite.UTF8String, -1, &stmt, NULL);
    NSDate *finishTime = [NSDate date];
    NSTimeInterval time = [finishTime timeIntervalSinceDate:startTime];
    NSLog(@"match time:%lf", time);
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

+ (int)insertDataToFts:(NSDictionary *)data {
    const char *type = [self getCharDataWithCol:@"type" InDataDictionary:data];
    const char *col1 = [self getCharDataWithCol:@"col1" InDataDictionary:data];
    const char *col2 = [self getCharDataWithCol:@"col2" InDataDictionary:data];
    const char *col3 = [self getCharDataWithCol:@"col3" InDataDictionary:data];
    const char *col4 = [self getCharDataWithCol:@"col4" InDataDictionary:data];
    const char *col5 = [self getCharDataWithCol:@"col5" InDataDictionary:data];
    const char *uCol1 = [self getCharDataWithCol:@"uCol1" InDataDictionary:data];
    const char *uCol2 = [self getCharDataWithCol:@"uCol2" InDataDictionary:data];
    const char *uCol3 = [self getCharDataWithCol:@"uCol3" InDataDictionary:data];
    const char *uCol4 = [self getCharDataWithCol:@"uCol4" InDataDictionary:data];
    const char *uCol5 = [self getCharDataWithCol:@"uCol5" InDataDictionary:data];
    const char *uCol6 = [self getCharDataWithCol:@"uCol6" InDataDictionary:data];
    const char *uCol7 = [self getCharDataWithCol:@"uCol7" InDataDictionary:data];
    const char *uCol8 = [self getCharDataWithCol:@"uCol8" InDataDictionary:data];
    const char *uCol9 = [self getCharDataWithCol:@"uCol9" InDataDictionary:data];
    const char *uCol10 = [self getCharDataWithCol:@"uCol10" InDataDictionary:data];
    int result = insert_fts(type, col1, col2, col3, col4, col5, uCol1, uCol2, uCol3, uCol4, uCol5, uCol6, uCol7, uCol8, uCol9, uCol10);
    return result;
}

+ (int)insertArrayToFts:(NSArray *)array {
    for (NSDictionary *data in array) {
        int result = [self insertDataToFts:data];
        if (result != SQLITE_OK) {
            return result;
        }
    }
    return SQLITE_OK;
}

+ (const char *)getCharDataWithCol:(NSString *)col InDataDictionary:(NSDictionary *)dictionary {
    NSString *colString = [dictionary objectForKey:col];
    if (![colString isKindOfClass:[NSString class]]) {
        return "\0";
    }
    const char *colCharData = [colString cStringUsingEncoding:NSUTF8StringEncoding];
    return colCharData;
}

@end
