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

+ (int)insertArrayToSimpleFts:(NSArray *)array;
+ (int)deleteArrayFromSimpleFTS:(NSArray *)array;
+ (int)updateArrayFromSimpleFTS:(NSArray *)array;

+ (int)insertArrayToMutipleFts:(NSArray *)array;
+ (int)deleteArrayFromMutipleFTS:(NSArray *)array;
+ (int)updateArrayFromMutipleFTS:(NSArray *)array;

@end
