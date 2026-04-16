#ifndef CACHE_H
#define CACHE_H
#include<bits/stdc++.h>
using namespace std;
const int blockSize=4;///word
struct word{
   string s;
};
struct CacheBlock{
   string tag;
   int valid_bit;
   int isDirty;
   word data[blockSize];
   int memBlockNum;
};
class cache{
   private:
   public:
   virtual CacheBlock* findBlock(string Tag,int memBlockNum)=0;
   virtual CacheBlock setBlock(CacheBlock b)=0;
};
#endif