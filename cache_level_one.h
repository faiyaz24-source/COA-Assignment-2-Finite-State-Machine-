#ifndef CACHE_LEVEL_ONE_H
#define CACHE_LEVEL_ONE_H
#include "cache.h"
#include<bits/stdc++.h>
using namespace std;
const int L1cacheSize=10;
class cache_Level_one:public cache{///fully associative
   private:
   CacheBlock storage[L1cacheSize];
   int nextToReplace;
   public:
   cache_Level_one();
   CacheBlock* findBlock(string Tag,int memBlockNum);
   CacheBlock setBlock(CacheBlock b);
   void printCachStatus();
   CacheBlock getStorage(int i);
};


#endif
