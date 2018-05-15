//
//  sqlite_fts_util.cpp
//  FTS5Demo
//
//  Created by 徐梦华 on 2018/5/14.
//  Copyright © 2018年 Xu Menghua. All rights reserved.
//

#include "sqlite_fts_util.hpp"
extern "C"{
#include "sqlite_fts_util.h"
}
#include <string.h>

#define STRING_BUFFER_LENGTH 16384

using namespace std;

const char* getValue(map<string,string> dataMap, string key);

int insertVectorToSimpleFts(vector<map<string,string>> dataVector) {
    beginTransaction();
    for (int i = 0; i < dataVector.size(); i++) {
        map<string,string> dataMap = dataVector[i];
        size_t size = sizeof(char)*STRING_BUFFER_LENGTH;
        char *data_id = (char*)malloc(size);
        memset(data_id, '\0', size);
        strcpy(data_id, getValue(dataMap, "data_id"));
        char *type = (char*)malloc(size);
        memset(type, '\0', size);
        strcpy(type, getValue(dataMap, "type"));
        char *data1 = (char*)malloc(size);
        memset(data1, '\0', size);
        strcpy(data1, getValue(dataMap, "data1"));
        char *data2 = (char*)malloc(size);
        memset(data2, '\0', size);
        strcpy(data2, getValue(dataMap, "data2"));
        char *data3 = (char*)malloc(size);
        memset(data3, '\0', size);
        strcpy(data3, getValue(dataMap, "data3"));
        char *body = (char*)malloc(size);
        memset(body, '\0', size);
        strcpy(body, getValue(dataMap, "body"));
        int result = insertDataToSimpleFts(data_id, type, data1, data2, data3, body);
        free(data_id);
        free(type);
        free(data1);
        free(data2);
        free(data3);
        free(body);
        if (result == SQLITE_ERROR) {
            return result;
        }
    }
    commitTransaction();
    return SQLITE_OK;
}

int deleteVectorToSimpleFts(vector<map<string,string>> dataVector) {
    beginTransaction();
    for (int i = 0; i < dataVector.size(); i++) {
        map<string,string> dataMap = dataVector[i];
        size_t size = sizeof(char)*STRING_BUFFER_LENGTH;
        char *data_id = (char*)malloc(size);
        memset(data_id, '\0', size);
        strcpy(data_id, getValue(dataMap, "data_id"));
        int result = deleteFromSimpleFtsById(data_id);
        free(data_id);
        if (result == SQLITE_ERROR) {
            return result;
        }
    }
    commitTransaction();
    return SQLITE_OK;
}

int updateVectorToSimpleFts(vector<map<string,string>> dataVector) {
    beginTransaction();
    for (int i = 0; i < dataVector.size(); i++) {
        map<string,string> dataMap = dataVector[i];
        size_t size = sizeof(char)*STRING_BUFFER_LENGTH;
        char *data_id = (char*)malloc(size);
        memset(data_id, '\0', size);
        strcpy(data_id, getValue(dataMap, "data_id"));
        char *type = (char*)malloc(size);
        memset(type, '\0', size);
        strcpy(type, getValue(dataMap, "type"));
        char *data1 = (char*)malloc(size);
        memset(data1, '\0', size);
        strcpy(data1, getValue(dataMap, "data1"));
        char *data2 = (char*)malloc(size);
        memset(data2, '\0', size);
        strcpy(data2, getValue(dataMap, "data2"));
        char *data3 = (char*)malloc(size);
        memset(data3, '\0', size);
        strcpy(data3, getValue(dataMap, "data3"));
        char *body = (char*)malloc(size);
        memset(body, '\0', size);
        strcpy(body, getValue(dataMap, "body"));
        int result = updateSimpleFtsByid(data_id, type, data1, data2, data3, body);
        free(data_id);
        free(type);
        free(data1);
        free(data2);
        free(data3);
        free(body);
        if (result == SQLITE_ERROR) {
            return result;
        }
    }
    commitTransaction();
    return SQLITE_OK;
}

int insertVectorToMutipleFts(vector<map<string,string>> dataVector) {
    beginTransaction();
    for (int i = 0; i < dataVector.size(); i++) {
        map<string,string> dataMap = dataVector[i];
        size_t size = sizeof(char)*STRING_BUFFER_LENGTH;
        char *data_id = (char*)malloc(size);
        memset(data_id, '\0', size);
        strcpy(data_id, getValue(dataMap, "data_id"));
        char *type = (char*)malloc(size);
        memset(type, '\0', size);
        strcpy(type, getValue(dataMap, "type"));
        char *data1 = (char*)malloc(size);
        memset(data1, '\0', size);
        strcpy(data1, getValue(dataMap, "data1"));
        char *data2 = (char*)malloc(size);
        memset(data2, '\0', size);
        strcpy(data2, getValue(dataMap, "data2"));
        char *data3 = (char*)malloc(size);
        memset(data3, '\0', size);
        strcpy(data3, getValue(dataMap, "data3"));
        char *body1 = (char*)malloc(size);
        memset(body1, '\0', size);
        strcpy(body1, getValue(dataMap, "body1"));
        char *body2 = (char*)malloc(size);
        memset(body2, '\0', size);
        strcpy(body2, getValue(dataMap, "body2"));
        char *body3 = (char*)malloc(size);
        memset(body3, '\0', size);
        strcpy(body3, getValue(dataMap, "body3"));
        int result = insertDataToMutipleFts(data_id, type, data1, data2, data3, body1, body2, body3);
        free(data_id);
        free(type);
        free(data1);
        free(data2);
        free(data3);
        free(body1);
        free(body2);
        free(body3);
        if (result == SQLITE_ERROR) {
            return result;
        }
    }
    commitTransaction();
    return SQLITE_OK;
}

int deleteVectorToMutipleFts(vector<map<string,string>> dataVector) {
    beginTransaction();
    for (int i = 0; i < dataVector.size(); i++) {
        map<string,string> dataMap = dataVector[i];
        size_t size = sizeof(char)*STRING_BUFFER_LENGTH;
        char *data_id = (char*)malloc(size);
        memset(data_id, '\0', size);
        strcpy(data_id, getValue(dataMap, "data_id"));
        int result = deleteFromMutipleFtsById(data_id);
        free(data_id);
        if (result == SQLITE_ERROR) {
            return result;
        }
    }
    commitTransaction();
    return SQLITE_OK;
}

int updateVectorToMutipleFts(vector<map<string,string>> dataVector) {
    beginTransaction();
    for (int i = 0; i < dataVector.size(); i++) {
        map<string,string> dataMap = dataVector[i];
        size_t size = sizeof(char)*STRING_BUFFER_LENGTH;
        char *data_id = (char*)malloc(size);
        memset(data_id, '\0', size);
        strcpy(data_id, getValue(dataMap, "data_id"));
        char *type = (char*)malloc(size);
        memset(type, '\0', size);
        strcpy(type, getValue(dataMap, "type"));
        char *data1 = (char*)malloc(size);
        memset(data1, '\0', size);
        strcpy(data1, getValue(dataMap, "data1"));
        char *data2 = (char*)malloc(size);
        memset(data2, '\0', size);
        strcpy(data2, getValue(dataMap, "data2"));
        char *data3 = (char*)malloc(size);
        memset(data3, '\0', size);
        strcpy(data3, getValue(dataMap, "data3"));
        char *body1 = (char*)malloc(size);
        memset(body1, '\0', size);
        strcpy(body1, getValue(dataMap, "body1"));
        char *body2 = (char*)malloc(size);
        memset(body2, '\0', size);
        strcpy(body2, getValue(dataMap, "body2"));
        char *body3 = (char*)malloc(size);
        memset(body3, '\0', size);
        strcpy(body3, getValue(dataMap, "body3"));
        int result = updateMutipleFtsById(data_id, type, data1, data2, data3, body1, body2, body3);
        free(data_id);
        free(type);
        free(data1);
        free(data2);
        free(data3);
        free(body1);
        free(body2);
        free(body3);
        if (result == SQLITE_ERROR) {
            return result;
        }
    }
    commitTransaction();
    return SQLITE_OK;
}

const char* getValue(map<string,string> dataMap, string key) {
    map<string,string>::iterator it = dataMap.find(key);
    const char *value = it->second.c_str();
    return value;
}
