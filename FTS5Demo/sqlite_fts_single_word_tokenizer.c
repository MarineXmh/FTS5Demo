//
//  sqlite_fts_single_word_icu_tokenizer.c
//  FTS5Demo
//
//  Created by Xu Menghua on 2018/1/5.
//  Copyright © 2018年 Xu Menghua. All rights reserved.
//

#include "sqlite_fts_single_word_tokenizer.h"
#include <CoreFoundation/CoreFoundation.h>

typedef struct Fts5SingleWordTokenizerContext Fts5SingleWordTokenizerContext;
typedef struct Fts5SingleWordTokenizerModule Fts5SingleWordTokenizerModule;

struct Fts5SingleWordTokenizerContext {
    void *pCtx;
    int (*xToken)(void*, int, const char*, int, int, int);
};

struct Fts5SingleWordTokenizerModule {
    Fts5SingleWordTokenizerContext *pContext;
};

fts5_api *fts5_api_from_db(sqlite3 *db) {
    fts5_api *pRet = 0;
    sqlite3_stmt *pStmt = 0;

    if(SQLITE_OK == sqlite3_prepare_v2(db, "SELECT fts5(?1)", -1, &pStmt, 0)){
        sqlite3_bind_pointer(pStmt, 1, (void*)&pRet, "fts5_api_ptr", NULL);
        sqlite3_step(pStmt);
    }
    sqlite3_finalize(pStmt);
    return pRet;
}
int fts5SSingleWordTokenizerCreate(void *pCtx, const char **azArg, int nArg, Fts5Tokenizer **ppOut);
void fts5SingleWordTokenizerDelete(Fts5Tokenizer *pTok);
int fts5SingleWordTokenize(Fts5Tokenizer *pTokenizer, void *pCtx, int flags, const char *pText, int nText, int (*xToken)(void *pCtx, int tflags, const char *pToken, int nToken, int iStart, int iEnd));
static void fts5SingleWordDeleteTokenizerModule(void *pCtx);

int create_single_word_tokenizer(sqlite3 *db, const char * zName, void *userData) {
    fts5_api *pApi = fts5_api_from_db(db);
    Fts5SingleWordTokenizerContext *context = malloc(sizeof(Fts5SingleWordTokenizerContext));
    context->pCtx = userData;
    Fts5SingleWordTokenizerModule  *module = malloc(sizeof(Fts5SingleWordTokenizerModule));
    module->pContext = context;
    fts5_tokenizer singleWordTokenizer;
    singleWordTokenizer.xCreate = fts5SSingleWordTokenizerCreate;
    singleWordTokenizer.xDelete = fts5SingleWordTokenizerDelete;
    singleWordTokenizer.xTokenize = fts5SingleWordTokenize;
    int rc = pApi->xCreateTokenizer(pApi, zName, (void*)module, &singleWordTokenizer, fts5SingleWordDeleteTokenizerModule);
    if (rc != SQLITE_OK) {
        printf("create tokenizer failed\n");
    }
    return rc;
}

static void fts5SingleWordDeleteTokenizerModule(void *pCtx) {
    Fts5SingleWordTokenizerModule *pMod = (Fts5SingleWordTokenizerModule*)pCtx;
    free(pMod->pContext);
    free(pMod);
}

int fts5SSingleWordTokenizerCreate(void *pCtx, const char **azArg, int nArg, Fts5Tokenizer **ppOut) {
    int rc = SQLITE_OK;
    *ppOut = (Fts5Tokenizer *)pCtx;
    return rc;
}

void fts5SingleWordTokenizerDelete(Fts5Tokenizer *pTok) {
    sqlite3_free(pTok);
}

int fts5SingleWordTokenize(Fts5Tokenizer *pTokenizer, void *pCtx, int flags, const char *pText, int nText, int (*xToken)(void *pCtx, int tflags, const char *pToken, int nToken, int iStart, int iEnd)) {
    CFStringRef dTextRef = CFStringCreateWithCString(kCFAllocatorDefault, pText, kCFStringEncodingUTF8);
    CFMutableStringRef mdTextRef = CFStringCreateMutableCopy(kCFAllocatorDefault, nText, dTextRef);
    CFStringTrimWhitespace(mdTextRef);
    
    CFIndex stringLength = CFStringGetLength(mdTextRef);

    int index = 0;
    int rc = SQLITE_OK;
    for (; index < stringLength; index++) {
        CFStringRef characterRef = CFStringCreateWithSubstring(kCFAllocatorDefault, mdTextRef, CFRangeMake(index, 1));
        CFIndex characterLength = CFStringGetLength(characterRef);
        CFIndex characterMaxSize = CFStringGetMaximumSizeForEncoding(characterLength, kCFStringEncodingUTF8)+1;
        char *character = (char*)malloc(characterMaxSize);
        memset(character, '\0', characterMaxSize);
        if (CFStringGetCString(characterRef, character, characterMaxSize, kCFStringEncodingUTF8)) {
            int nToken = (int)strlen(character);
            int iStartOffset = index;
            int iEndOffset = index + nToken;
            rc = xToken(pCtx, 0, character, nToken, iStartOffset, iEndOffset);
            if (rc != SQLITE_OK) {
                free(character);
                CFRelease(characterRef);
                CFRelease(dTextRef);
                CFRelease(mdTextRef);
                return rc;
            }
        } else {
            printf("tokenize error\n");
        }
        free(character);
        CFRelease(characterRef);
    }
    if (rc == SQLITE_DONE) {
        rc = SQLITE_OK;
    }
    CFRelease(dTextRef);
    CFRelease(mdTextRef);
    return rc;
}

