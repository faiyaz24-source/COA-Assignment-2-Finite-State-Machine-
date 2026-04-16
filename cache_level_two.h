#ifndef CACHE_LEVEL_TWO_H
#define CACHE_LEVEL_TWO_H
#include "cache.h"
#include "cache_level_one.h"
#include<bits/stdc++.h>
using namespace std;
const int L2CashAssociativity=4;
const int L2CashSize=20;
const int  L2CashGroupSize=L2CashSize/L2CashAssociativity;
class cache_Level_two:public cache{///4 way associative
    private:
    CacheBlock storage[L2CashAssociativity][L2CashGroupSize];
    int nextToReplace[L2CashAssociativity];
    public:
    cache_Level_two();
    CacheBlock* findBlock(string Tag,int memBlockNum);
    CacheBlock setBlock(CacheBlock b);
    void printStatus();
    CacheBlock getStorage(int i,int j);
}; 
#endif