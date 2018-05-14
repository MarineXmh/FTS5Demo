//
//  SqliteFTSManager.h
//  FTS5Demo
//
//  Created by Xu Menghua on 2018/1/3.
//  Copyright © 2018年 Xu Menghua. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface SqliteFTSManager : NSObject

+ (instancetype)sharedManager;
- (void)initFTS;

@end
