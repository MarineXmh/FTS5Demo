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

#define STRING_BUFFER_LENGTH 16384

using namespace std;

const char* getValue(map<string,string> dataMap, string key);

int insertVectorToSimpleFts(vector<map<string,string>> dataVector) {
    beginTransaction();
    for (int i = 0; i < dataVector.size(); i++) {
        map<string,string> dataMap = dataVector[i];
        const char *data_id = getValue(dataMap, "data_id");
        const char *type = getValue(dataMap, "type");
        const char *data1 = getValue(dataMap, "data1");
        const char *data2 = getValue(dataMap, "data2");
        const char *data3 = getValue(dataMap, "data3");
        const char *body = getValue(dataMap, "body");
        int result = insertDataToSimpleFts(data_id, type, data1, data2, data3, body);
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
        const char *data_id = getValue(dataMap, "data_id");
        int result = deleteFromSimpleFtsById(data_id);
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
        const char *data_id = getValue(dataMap, "data_id");
        const char *type = getValue(dataMap, "type");
        const char *data1 = getValue(dataMap, "data1");
        const char *data2 = getValue(dataMap, "data2");
        const char *data3 = getValue(dataMap, "data3");
        const char *body = getValue(dataMap, "body");
        int result = updateSimpleFtsByid(data_id, type, data1, data2, data3, body);
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
        const char *data_id = getValue(dataMap, "data_id");
        const char *type = getValue(dataMap, "type");
        const char *data1 = getValue(dataMap, "data1");
        const char *data2 = getValue(dataMap, "data2");
        const char *data3 = getValue(dataMap, "data3");
        const char *body1 = getValue(dataMap, "body1");
        const char *body2 = getValue(dataMap, "body2");
        const char *body3 = getValue(dataMap, "body3");
        int result = insertDataToMutipleFts(data_id, type, data1, data2, data3, body1, body2, body3);
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
        const char *data_id = getValue(dataMap, "data_id");
        int result = deleteFromMutipleFtsById(data_id);
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
        const char *data_id = getValue(dataMap, "data_id");
        const char *type = getValue(dataMap, "type");
        const char *data1 = getValue(dataMap, "data1");
        const char *data2 = getValue(dataMap, "data2");
        const char *data3 = getValue(dataMap, "data3");
        const char *body1 = getValue(dataMap, "body1");
        const char *body2 = getValue(dataMap, "body2");
        const char *body3 = getValue(dataMap, "body3");
        int result = updateMutipleFtsById(data_id, type, data1, data2, data3, body1, body2, body3);
        if (result == SQLITE_ERROR) {
            return result;
        }
    }
    commitTransaction();
    return SQLITE_OK;
}

const char* getValue(map<string,string> dataMap, string key) {
    map<string,string>::iterator it = dataMap.find(key);
    return it->second.c_str();
}
