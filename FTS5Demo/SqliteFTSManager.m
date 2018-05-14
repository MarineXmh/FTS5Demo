//
//  SqliteFTSManager.m
//  FTS5Demo
//
//  Created by Xu Menghua on 2018/1/3.
//  Copyright © 2018年 Xu Menghua. All rights reserved.
//

#import "SqliteFTSManager.h"
#import "sqlite_fts_util.h"
#import "sqlite_fts_single_word_tokenizer.h"

#define kFTSDBFilename @"sqlite_fts.sqlite"

@interface SqliteFTSManager()


@end

@implementation SqliteFTSManager

- (void)initFTS {
    [self setDBPath];
    if (openFtsDb() == SQLITE_OK) {
        if (createTokenizer() == SQLITE_OK) {
            [self createTables];
        }
        if (turnOffSynchronous() == SQLITE_OK) {
            NSLog(@"turnOffSynchronous");
        }
    }
}

- (void)setDBPath {
    NSString *documentPath = [NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES) firstObject];
    NSString *filePath = [documentPath stringByAppendingPathComponent:kFTSDBFilename];
    setSqliteFtsDbPath(filePath.UTF8String);
}

- (void)createTables {
    createSimpleFtsTable();
    createMutipleFtsTable();
}

#pragma mark - singleton

static SqliteFTSManager *_instance;

+ (instancetype)sharedManager {
    return [[self alloc] init];
}

+ (instancetype)allocWithZone:(struct _NSZone *)zone {
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        if (_instance == nil) {
            _instance = [super allocWithZone:zone];
        }
    });
    return _instance;
}

- (id)copyWithZone:(NSZone *)zone {
    return _instance;
}

- (id)mutableCopyWithZone:(NSZone *)zone {
    return _instance;
}

@end
