//
//  sqlite_fts_single_word_icu_tokenizer.c
//  FTS5Demo
//
//  Created by Xu Menghua on 2018/1/5.
//  Copyright © 2018年 Xu Menghua. All rights reserved.
//

#include "sqlite_fts_single_word_tokenizer.h"
#include <string.h>
#include <stdlib.h>

#define STRING_BUFFER_LENGTH 16384

typedef struct Fts5SingleWordTokenizerContext Fts5SingleWordTokenizerContext;
typedef struct Fts5SingleWordTokenizerModule Fts5SingleWordTokenizerModule;

char* subString(const char *str, unsigned int start, unsigned int end);

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
    int index = 0;
    int rc = SQLITE_OK;
    while (index < nText) {
        const unsigned char ch = pText[index];
        int nToken = 0;
        if (ch < 0xC0) {
            nToken = 1;
        } else if (ch < 0xF0) {
            if (ch < 0xE0) {
                nToken = 2;
            } else {
                nToken = 3;
            }
        } else {
            if (ch < 0xF8) {
                nToken = 4;
            } else if (ch < 0xFC) {
                nToken = 5;
            } else {
                nToken = 6;
            }
        }
        int iStartOffset = index;
        int iEndOffset = index + nToken;
        char *token = subString(pText, iStartOffset, iEndOffset);
        rc = xToken(pCtx, 0, token, nToken, iStartOffset, iEndOffset);
        if (rc != SQLITE_OK) {
            printf("tokenize error\n");
            return rc;
        }
        index += nToken;
    }
    if (rc == SQLITE_DONE) {
        rc = SQLITE_OK;
    }
    return rc;
}

char* subString(const char *str, unsigned int start, unsigned int end) {
    unsigned int n = end - start;
    static char strBuf[STRING_BUFFER_LENGTH];
    strncpy(strBuf, str + start, n);
    strBuf[n] = '\0';
    return strBuf;
}
