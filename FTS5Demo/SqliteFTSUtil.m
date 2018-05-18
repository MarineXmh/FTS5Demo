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
    sqlite3 *db = getSqliteFtsUtilDb();
    NSString *sqlite = [NSString stringWithFormat:@"SELECT * FROM %@ WHERE %@ MATCH '%@'", table, column, match];
    sqlite3_stmt *stmt = NULL;
    int result = sqlite3_prepare_v2(db, sqlite.UTF8String, -1, &stmt, NULL);
    if (result == SQLITE_OK) {
        int columnCount = sqlite3_column_count(stmt);
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            NSMutableDictionary *data = [NSMutableDictionary dictionary];
            for (int i = 0; i < columnCount; i++) {
                NSString *text = [NSString stringWithUTF8String:(const char *)sqlite3_column_text(stmt, i)];
                if (text == nil) {
                    text = @"";
                }
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

+ (int)insertArrayToSimpleFts:(NSArray *)array {
    beginTransaction();
//    sqlite3_stmt *stmt = NULL;
//    sqlite3 *db = getSqliteFtsDb();
//    int result = sqlite3_prepare_v2(db, kInsertToSimpleFtsTableBindSQL, (int)strlen(kInsertToSimpleFtsTableBindSQL), &stmt, NULL);
//    if (result != SQLITE_OK) {
//        return result;
//    }
    for (NSDictionary *data in array) {
        const char *data_id = [self getCharDataWithCol:@"data_id" InDataDictionary:data];
        const char *type = [self getCharDataWithCol:@"type" InDataDictionary:data];
        const char *data1 = [self getCharDataWithCol:@"data1" InDataDictionary:data];
        const char *data2 = [self getCharDataWithCol:@"data2" InDataDictionary:data];
        const char *data3 = [self getCharDataWithCol:@"data3" InDataDictionary:data];
        const char *body = [self getCharDataWithCol:@"body" InDataDictionary:data];
        int result = insertDataToSimpleFts(data_id, type, data1, data2, data3, body);
        if (result == SQLITE_ERROR) {
            return result;
        }
//        sqlite3_bind_text(stmt, 1, data_id, (int)strlen(data_id), SQLITE_TRANSIENT);
//        sqlite3_bind_text(stmt, 2, type, (int)strlen(type), SQLITE_TRANSIENT);
//        sqlite3_bind_text(stmt, 3, data1, (int)strlen(data1), SQLITE_TRANSIENT);
//        sqlite3_bind_text(stmt, 4, data2, (int)strlen(data2), SQLITE_TRANSIENT);
//        sqlite3_bind_text(stmt, 5, data3, (int)strlen(data3), SQLITE_TRANSIENT);
//        sqlite3_bind_text(stmt, 6, body, (int)strlen(body), SQLITE_TRANSIENT);
//        int result = sqlite3_step(stmt);
//        if (result == SQLITE_ERROR) {
//            return result;
//        }
    }
    commitTransaction();
//    sqlite3_finalize(stmt);
    return SQLITE_OK;
}

+ (int)deleteArrayFromSimpleFTS:(NSArray *)array {
    beginTransaction();
//    sqlite3_stmt *stmt = NULL;
//    sqlite3 *db = getSqliteFtsDb();
//    int result = sqlite3_prepare_v2(db, kDeleteFromSimpleFtsTableByIdBindSQL, (int)strlen(kDeleteFromSimpleFtsTableByIdBindSQL), &stmt, NULL);
//    if (result != SQLITE_OK) {
//        return result;
//    }
    for (NSDictionary *data in array) {
        const char *data_id = [self getCharDataWithCol:@"data_id" InDataDictionary:data];
        int result = deleteFromSimpleFtsById(data_id);
        if (result == SQLITE_ERROR) {
            return result;
        }
//        sqlite3_bind_text(stmt, 1, data_id, (int)strlen(data_id), SQLITE_TRANSIENT);
//        int result = sqlite3_step(stmt);
//        if (result == SQLITE_ERROR) {
//            return result;
//        }
    }
    commitTransaction();
//    sqlite3_finalize(stmt);
    return SQLITE_OK;
}

+ (int)updateArrayFromSimpleFTS:(NSArray *)array {
    beginTransaction();
//    sqlite3_stmt *stmt = NULL;
//    sqlite3 *db = getSqliteFtsDb();
//    int result = sqlite3_prepare_v2(db, kUpdateSimpleFtsTableByIdBindSQL, (int)strlen(kUpdateSimpleFtsTableByIdBindSQL), &stmt, NULL);
//    if (result != SQLITE_OK) {
//        return result;
//    }
    for (NSDictionary *data in array) {
        const char *data_id = [self getCharDataWithCol:@"data_id" InDataDictionary:data];
        const char *type = [self getCharDataWithCol:@"type" InDataDictionary:data];
        const char *data1 = [self getCharDataWithCol:@"data1" InDataDictionary:data];
        const char *data2 = [self getCharDataWithCol:@"data2" InDataDictionary:data];
        const char *data3 = [self getCharDataWithCol:@"data3" InDataDictionary:data];
        const char *body = [self getCharDataWithCol:@"body" InDataDictionary:data];
        int result = updateSimpleFtsByid(data_id, type, data1, data2, data3, body);
//        sqlite3_bind_text(stmt, 1, data_id, (int)strlen(data_id), SQLITE_TRANSIENT);
//        sqlite3_bind_text(stmt, 2, type, (int)strlen(type), SQLITE_TRANSIENT);
//        sqlite3_bind_text(stmt, 3, data1, (int)strlen(data1), SQLITE_TRANSIENT);
//        sqlite3_bind_text(stmt, 4, data2, (int)strlen(data2), SQLITE_TRANSIENT);
//        sqlite3_bind_text(stmt, 5, data3, (int)strlen(data3), SQLITE_TRANSIENT);
//        sqlite3_bind_text(stmt, 6, body, (int)strlen(body), SQLITE_TRANSIENT);
//        sqlite3_bind_text(stmt, 7, data_id, (int)strlen(data_id), SQLITE_TRANSIENT);
//        int result = sqlite3_step(stmt);
        if (result == SQLITE_ERROR) {
            return result;
        }
    }
    commitTransaction();
//    sqlite3_finalize(stmt);
    return SQLITE_OK;
}

+ (int)insertArrayToMutipleFts:(NSArray *)array {
    beginTransaction();
    //    sqlite3_stmt *stmt = NULL;
    //    sqlite3 *db = getSqliteFtsDb();
    //    int result = sqlite3_prepare_v2(db, kInsertToSimpleFtsTableBindSQL, (int)strlen(kInsertToSimpleFtsTableBindSQL), &stmt, NULL);
    //    if (result != SQLITE_OK) {
    //        return result;
    //    }
    for (NSDictionary *data in array) {
        const char *data_id = [self getCharDataWithCol:@"data_id" InDataDictionary:data];
        const char *type = [self getCharDataWithCol:@"type" InDataDictionary:data];
        const char *data1 = [self getCharDataWithCol:@"data1" InDataDictionary:data];
        const char *data2 = [self getCharDataWithCol:@"data2" InDataDictionary:data];
        const char *data3 = [self getCharDataWithCol:@"data3" InDataDictionary:data];
        const char *body1 = [self getCharDataWithCol:@"body1" InDataDictionary:data];
        const char *body2 = [self getCharDataWithCol:@"body2" InDataDictionary:data];
        const char *body3 = [self getCharDataWithCol:@"body3" InDataDictionary:data];
        int result = insertDataToMutipleFts(data_id, type, data1, data2, data3, body1, body2, body3);
        if (result == SQLITE_ERROR) {
            return result;
        }
        //        sqlite3_bind_text(stmt, 1, data_id, (int)strlen(data_id), SQLITE_TRANSIENT);
        //        sqlite3_bind_text(stmt, 2, type, (int)strlen(type), SQLITE_TRANSIENT);
        //        sqlite3_bind_text(stmt, 3, data1, (int)strlen(data1), SQLITE_TRANSIENT);
        //        sqlite3_bind_text(stmt, 4, data2, (int)strlen(data2), SQLITE_TRANSIENT);
        //        sqlite3_bind_text(stmt, 5, data3, (int)strlen(data3), SQLITE_TRANSIENT);
        //        sqlite3_bind_text(stmt, 6, body, (int)strlen(body), SQLITE_TRANSIENT);
        //        int result = sqlite3_step(stmt);
        //        if (result == SQLITE_ERROR) {
        //            return result;
        //        }
    }
    commitTransaction();
    //    sqlite3_finalize(stmt);
    return SQLITE_OK;
}

+ (int)deleteArrayFromMutipleFTS:(NSArray *)array {
    beginTransaction();
    //    sqlite3_stmt *stmt = NULL;
    //    sqlite3 *db = getSqliteFtsDb();
    //    int result = sqlite3_prepare_v2(db, kDeleteFromSimpleFtsTableByIdBindSQL, (int)strlen(kDeleteFromSimpleFtsTableByIdBindSQL), &stmt, NULL);
    //    if (result != SQLITE_OK) {
    //        return result;
    //    }
    for (NSDictionary *data in array) {
        const char *data_id = [self getCharDataWithCol:@"data_id" InDataDictionary:data];
        int result = deleteFromMutipleFtsById(data_id);
        if (result == SQLITE_ERROR) {
            return result;
        }
        //        sqlite3_bind_text(stmt, 1, data_id, (int)strlen(data_id), SQLITE_TRANSIENT);
        //        int result = sqlite3_step(stmt);
        //        if (result == SQLITE_ERROR) {
        //            return result;
        //        }
    }
    commitTransaction();
    //    sqlite3_finalize(stmt);
    return SQLITE_OK;
}

+ (int)updateArrayFromMutipleFTS:(NSArray *)array {
    beginTransaction();
    //    sqlite3_stmt *stmt = NULL;
    //    sqlite3 *db = getSqliteFtsDb();
    //    int result = sqlite3_prepare_v2(db, kUpdateSimpleFtsTableByIdBindSQL, (int)strlen(kUpdateSimpleFtsTableByIdBindSQL), &stmt, NULL);
    //    if (result != SQLITE_OK) {
    //        return result;
    //    }
    for (NSDictionary *data in array) {
        const char *data_id = [self getCharDataWithCol:@"data_id" InDataDictionary:data];
        const char *type = [self getCharDataWithCol:@"type" InDataDictionary:data];
        const char *data1 = [self getCharDataWithCol:@"data1" InDataDictionary:data];
        const char *data2 = [self getCharDataWithCol:@"data2" InDataDictionary:data];
        const char *data3 = [self getCharDataWithCol:@"data3" InDataDictionary:data];
        const char *body1 = [self getCharDataWithCol:@"body1" InDataDictionary:data];
        const char *body2 = [self getCharDataWithCol:@"body2" InDataDictionary:data];
        const char *body3 = [self getCharDataWithCol:@"body3" InDataDictionary:data];
        int result = updateMutipleFtsById(data_id, type, data1, data2, data3, body1, body2, body3);
        //        sqlite3_bind_text(stmt, 1, data_id, (int)strlen(data_id), SQLITE_TRANSIENT);
        //        sqlite3_bind_text(stmt, 2, type, (int)strlen(type), SQLITE_TRANSIENT);
        //        sqlite3_bind_text(stmt, 3, data1, (int)strlen(data1), SQLITE_TRANSIENT);
        //        sqlite3_bind_text(stmt, 4, data2, (int)strlen(data2), SQLITE_TRANSIENT);
        //        sqlite3_bind_text(stmt, 5, data3, (int)strlen(data3), SQLITE_TRANSIENT);
        //        sqlite3_bind_text(stmt, 6, body, (int)strlen(body), SQLITE_TRANSIENT);
        //        sqlite3_bind_text(stmt, 7, data_id, (int)strlen(data_id), SQLITE_TRANSIENT);
        //        int result = sqlite3_step(stmt);
        if (result == SQLITE_ERROR) {
            return result;
        }
    }
    commitTransaction();
    //    sqlite3_finalize(stmt);
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
