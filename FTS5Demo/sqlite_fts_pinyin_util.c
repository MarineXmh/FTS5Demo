//
//  sqlite_fts_pinyin_util.c
//  FTS5Demo
//
//  Created by 徐梦华 on 2018/5/17.
//  Copyright © 2018年 Xu Menghua. All rights reserved.
//

#include "sqlite_fts_pinyin_util.h"
#include <string.h>

#define STRING_MAX_COLUNM 100
#define STRING_BUFFER_LENGTH 8192
#define PIN_YIN_SEPERATOR '_'

char* transferPinyinToSearchFormat(const char *pinyin) {
    char pinyinTransfered[STRING_BUFFER_LENGTH] = {0};
    char pinyinBuffer[STRING_MAX_COLUNM][STRING_BUFFER_LENGTH] = {0};
    unsigned long pinyinLength = strlen(pinyin);
    if (pinyinLength == 0) {
        pinyinTransfered[0] = '\0';
        char *pPinyinTransfered = pinyinTransfered;
        return pPinyinTransfered;
    }
    int wordIndex = 0;
    int letterIndex = 0;
    for (int i = 0; i < pinyinLength; i++) {
        char c = pinyin[i];
        if (c == ' ') {
            wordIndex++;
            letterIndex = 0;
        } else {
            pinyinBuffer[wordIndex][letterIndex++] = c;
        }
    }
    int wordCount = wordIndex + 1;
    int pinyinTransferedIndex = 0;
    for (int i = 0; i < wordCount; i++) {
        for (int j = i; j < wordCount; j++) {
            char *pinyinWord = pinyinBuffer[j];
            unsigned long pinyinWordLength = strlen(pinyinWord);
            if (j == i && pinyinWordLength > 0) {
                pinyinTransfered[pinyinTransferedIndex++] = PIN_YIN_SEPERATOR;
            }
            for (int k = 0; k < pinyinWordLength; k++) {
                char c = pinyinWord[k];
                if (c == '\0') {
                    break;
                }
                pinyinTransfered[pinyinTransferedIndex++] = c;
            }
        }
    }
    for (int i = 0; i < wordCount; i++) {
        for (int j = i; j < wordCount; j++) {
            char *pinyinWord = pinyinBuffer[j];
            unsigned long pinyinWordLength = strlen(pinyinWord);
            if (j == i && pinyinWordLength > 0) {
                pinyinTransfered[pinyinTransferedIndex++] = PIN_YIN_SEPERATOR;
            }
            for (int k = 0; k < 1; k++) {
                char c = pinyinWord[k];
                if (c == '\0') {
                    break;
                }
                pinyinTransfered[pinyinTransferedIndex++] = c;
            }
        }
    }
    char *pPinyinTransfered = pinyinTransfered;
    return pPinyinTransfered;
}
