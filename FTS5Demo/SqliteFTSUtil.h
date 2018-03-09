//
//  SqliteFTSUtil.h
//  FTS5Demo
//
//  Created by Xu Menghua on 2018/1/4.
//  Copyright © 2018年 Xu Menghua. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface SqliteFTSUtil : NSObject

+ (NSMutableArray *)selectWithTable:(NSString *)table Column:(NSString *)column Match:(NSString *)match;
+ (int)executeWithSql:(NSString *)sql;
+ (int)insertDataToFts:(NSDictionary *)data;
+ (int)insertArrayToFts:(NSArray *)array;

@end
