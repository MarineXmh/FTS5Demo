//
//  FTSBaseObject.m
//  FTS5Demo
//
//  Created by Xu Menghua on 2018/3/12.
//  Copyright © 2018年 Xu Menghua. All rights reserved.
//

#import "FTSBaseObject.h"

@implementation FTSBaseObject

- (NSDictionary *)toDictionary {
    NSDictionary *dictionary = @{@"data_id":self.data_id, @"type":self.type};
    return dictionary;
}

- (instancetype)initWithDictionary:(NSDictionary *)dictionary {
    self = [super init];
    if (self) {
        self.data_id = [dictionary objectForKey:@"data_id"];
        self.type = [dictionary objectForKey:@"type"];
    }
    return self;
}

@end
