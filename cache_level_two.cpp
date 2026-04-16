#include "cache_level_two.h"

cache_Level_two::cache_Level_two(){
    for(int i=0;i<L2CashAssociativity;i++){
        for(int j=0;j<L2CashGroupSize;j++){
            storage[i][j].valid_bit=0;
            storage[i][j].isDirty=0;
        }
    }
    for(int i=0;i<L2CashAssociativity;i++){
        nextToReplace[i]=0;
    }
}
CacheBlock* cache_Level_two::findBlock(string Tag,int memBlockNum){
   int i=memBlockNum%L2CashAssociativity;
   for(int j=0;j<L2CashGroupSize;j++){
       if(storage[i][j].valid_bit && storage[i][j].tag==Tag){
           return &storage[i][j];
       }
   }
   return NULL;
}
CacheBlock cache_Level_two::setBlock(CacheBlock b){
    int i=b.memBlockNum%L2CashAssociativity;
    CacheBlock temp;
    temp=storage[i][nextToReplace[i]];
    temp.valid_bit=temp.isDirty;
    storage[i][nextToReplace[i]]=b;
    nextToReplace[i]=(nextToReplace[i]+1)%L2CashGroupSize;
    return temp;
}
void cache_Level_two::printStatus(){
    cout << "L2 Cache Status:\n";
    for(int i=0;i<L2CashAssociativity;i++){
        cout << "Group Offset: " << i << endl;
        for(int j=0;j<L2CashGroupSize;j++){
              CacheBlock k=storage[i][j];
              if(k.valid_bit){
                cout << "Dirty Bit: " << k.isDirty << " Tag: " << k.tag << " Memory Block Num: " << k.memBlockNum << endl;
                cout << "Data:\n";
                for(int f=0;f<blockSize;f++){
                   cout << "Word Offset: " << f << "word: " << k.data[f].s << endl;
                }
              }
        }
        cout << "\n";
    }
}
CacheBlock cache_Level_two::getStorage(int i,int j){
    return  storage[i][j];
}
