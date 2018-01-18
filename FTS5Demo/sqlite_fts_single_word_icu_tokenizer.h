//
//  sqlite_fts_single_word_icu_tokenizer.h
//  FTS5Demo
//
//  Created by Xu Menghua on 2018/1/5.
//  Copyright © 2018年 Xu Menghua. All rights reserved.
//

#ifndef SQLITE3_H
#include "sqlite3.h"
#endif

#ifndef sqlite_fts_single_word_icu_tokenizer_h
#define sqlite_fts_single_word_icu_tokenizer_h

#include <stdio.h>

int create_single_word_tokenizer(sqlite3 *db, const char * zName, void *userData);

#endif /* sqlite_fts_single_word_icu_tokenizer_h */
