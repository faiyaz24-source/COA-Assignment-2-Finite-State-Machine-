#ifndef CACHE_CONTROLLER_H
#define CACHE_CONTROLLER_H
#include "cache.h"
#include "cache_level_one.h"
#include "cache_level_two.h"
#include "memory.h"
#include<bits/stdc++.h>
using namespace std;
class cachController{
    private:
    
    public:
    string readWord(int blockNum,string tag,int wordOffset,cache_Level_one &c1,cache_Level_two &c2,memory &m);
    void writeWord(int blockNum,string tag,int wordOffset,string toWrite,cache_Level_one &c1,cache_Level_two &c2,memory &m);
    void manageDirtyBlock_cach_level2(CacheBlock cb,cache_Level_two &c2,memory &m);
    void manageDirtyBlock_memory(CacheBlock cb,memory &m); 
    void manageAllDirtyBlock(cache_Level_one &c1,cache_Level_two &c2,memory &m);
};
#endif