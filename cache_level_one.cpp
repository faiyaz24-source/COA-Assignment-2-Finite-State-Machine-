#include "cache_level_one.h"

cache_Level_one::cache_Level_one(){
    for(int i=0;i<L1cacheSize;i++){
        storage[i].valid_bit=0;
        storage[i].isDirty=0;
     }
     nextToReplace=0;
}

CacheBlock* cache_Level_one::findBlock(string Tag,int memBlockNum){
    for(int i=0;i<L1cacheSize;i++){
        if(storage[i].valid_bit && storage[i].tag==Tag){
            return &storage[i];
        }
    }
    return NULL;
}

CacheBlock cache_Level_one::setBlock(CacheBlock b){
    CacheBlock temp;
    temp=storage[nextToReplace];
    temp.valid_bit=temp.isDirty;
    storage[nextToReplace]=b;
    nextToReplace=(nextToReplace+1)%L1cacheSize;
    return temp;
}
void cache_Level_one::printCachStatus(){
    cout << "L1 Cache Status:\n";
    for(int i=0;i<L1cacheSize;i++){
        CacheBlock k=storage[i];
        if(k.valid_bit){
            cout << "Dirty Bit: " << k.isDirty << " Tag: " << k.tag << " Memory Block Num: " << k.memBlockNum << endl;
            cout << "Data:\n";
            for(int j=0;j<blockSize;j++){
                cout << "Word Offset: " << j << "word: " << k.data[j].s << endl;
            }
        } 
    }
    cout << "\n";
}
CacheBlock cache_Level_one::getStorage(int i){
      return storage[i];
}