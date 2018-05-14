//
//  FTSBaseObject.h
//  FTS5Demo
//
//  Created by Xu Menghua on 2018/3/12.
//  Copyright © 2018年 Xu Menghua. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface FTSBaseObject : NSObject

@property (nonatomic, copy) NSString *data_id;
@property (nonatomic, copy) NSString *type;

// need override
- (NSDictionary *)toDictionary;
- (instancetype)initWithDictionary:(NSDictionary *)dictionary;
//

@end
