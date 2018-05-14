//
//  sqlite_fts_util.hpp
//  FTS5Demo
//
//  Created by 徐梦华 on 2018/5/14.
//  Copyright © 2018年 Xu Menghua. All rights reserved.
//

#ifndef sqlite_fts_util_hpp
#define sqlite_fts_util_hpp

#include <stdio.h>
#include <vector>
#include <map>
#include <string>

using namespace std;

int insertVectorToSimpleFts(vector<map<string,string>> dataVector);
int deleteVectorToSimpleFts(vector<map<string,string>> dataVector);
int updateVectorToSimpleFts(vector<map<string,string>> dataVector);

int insertVectorToMutipleFts(vector<map<string,string>> dataVector);
int deleteVectorToMutipleFts(vector<map<string,string>> dataVector);
int updateVectorToMutipleFts(vector<map<string,string>> dataVector);

#endif /* sqlite_fts_util_hpp */
