#ifndef MEMORY_H
#define MEMORY_H
#include<bits/stdc++.h>
#include "cache.h"
#include<fstream>
using namespace std;
const int memorySize=100;
struct memoryBlock{
   int blockNum;
   string tag;
   word data[blockSize];
};
class memory{
   private:
   memoryBlock storage[memorySize];
   public:
   string serialize(memoryBlock);
   memoryBlock deserialize(string);
   memoryBlock* findBlock(string tag,int blockNum);
   void updateBlock(CacheBlock cb);
   void printMemoryStatus(int memBlockNum);
   void printFullMemory();
   memory();
   ~memory();
};
#endif
