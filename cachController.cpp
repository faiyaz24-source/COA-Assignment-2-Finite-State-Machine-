#include "cachController.h"

string cachController::readWord(int blockNum,string tag,int wordOffset,cache_Level_one &c1,cache_Level_two &c2,memory &m){
    CacheBlock* cb;
    cb=c1.findBlock(tag,blockNum);
    if(cb){
        cout << "==================Cach hit in L1==============\n";
        return cb->data[wordOffset].s;
    }
    else{
        cout << "==================Cach Miss in L1==============\n";
        cb=c2.findBlock(tag,blockNum);
        if(cb){///is dirty handle
            cout << "===========================Cach Hit in L2============\n";
            cout << "===================Bringing Block "<<cb->memBlockNum<<" from L2 to L1==========\n";
            CacheBlock c_temp=(*cb);
            c_temp.isDirty=0;
            CacheBlock te=c1.setBlock(c_temp);
            if(te.isDirty && te.valid_bit){
                cout <<"============================Dirty Block detected in L1========================\n";
                cout << "===========================Write Back Block " << te.memBlockNum << " to L2====================\n";
               manageDirtyBlock_cach_level2(te,c2,m);
            }
            cout << "=============================Allocate Block from L2.Return to Cach test===========================\n"; 
            return cb->data[wordOffset].s;
        }
        else{
            cout << "===========================Cach miss on L2======================\n";
            cout << "==========================Need to Allocate Block from Memory=============\n";
            memoryBlock* mb=m.findBlock(tag,blockNum);
           CacheBlock c_temp;
           for(int i=0;i<blockSize;i++){
               c_temp.data[i]=mb->data[i];
           }
           c_temp.isDirty=0;
           c_temp.memBlockNum=mb->blockNum;
           c_temp.tag=mb->tag;
           c_temp.valid_bit=1;
           CacheBlock te=c2.setBlock(c_temp);
           if(te.isDirty && te.valid_bit){
             cout << "==========================Dirty Block detected in L2=====================\n";
             cout << "==========================Write Back Block " << te.memBlockNum << " to Memory=============\n";
             manageDirtyBlock_memory(te,m);
           }
           te=c1.setBlock(c_temp);
           if(te.isDirty && te.valid_bit){
             cout << "==========================Dirty Block detected in L1=====================\n";
             cout << "==========================Write Back Block " << te.memBlockNum << " to L2=============\n";
             manageDirtyBlock_cach_level2(te,c2,m);
           }
           return mb->data[wordOffset].s;
        }
    }
}
void cachController::manageDirtyBlock_memory(CacheBlock cb,memory &m){
   m.updateBlock(cb);
}
void cachController::manageDirtyBlock_cach_level2(CacheBlock cb,cache_Level_two &c2,memory &m){
    CacheBlock* temporal=c2.findBlock(cb.tag,cb.memBlockNum);
    if(temporal){
        temporal->valid_bit=0;
    }
    CacheBlock te=c2.setBlock(cb);
   if(te.isDirty && te.valid_bit){
      cout << "==========================Dirty Block detected in L2=====================\n";
      cout << "==========================Write Back Block " << te.memBlockNum << " to Memory=============\n";
      manageDirtyBlock_memory(te,m);
   }
}
void cachController::writeWord(int blockNum,string tag,int wordOffset,string toWrite,cache_Level_one &c1,cache_Level_two &c2,memory &m){
   CacheBlock* cb;
   cb=c1.findBlock(tag,blockNum);
   if(cb){
      cout << "=========================Cache Hit in L1===================\n";
      cout << "=========================Cache Block "<< cb->memBlockNum<<" updated and marked dirty=================\n";
      cb->data[wordOffset].s=toWrite;
      cb->isDirty=1;
   }
   else{
     cout << "=============================Write miss on L1=================\n";
     cb=c2.findBlock(tag,blockNum);
     if(cb){
        cout << "==================================Cache Hit in L2==========================\n";
        cout << "==================================Cach Block " << cb->memBlockNum << " Updated and Marked as Dirty=====================\n";
        cout << "==================================Need to Load it in L1=====================\n";
        cb->data[wordOffset].s=toWrite;
        cb->isDirty=1;
        CacheBlock te=(*cb);
        te.isDirty=0;
        te=c1.setBlock(te);
        if(te.isDirty && te.valid_bit){
            cout << "=============================Dirty Block detected in L1==========================\n";
            cout << "=============================Write back Block " << te.memBlockNum << " to L2 cache=========================\n"; 
            manageDirtyBlock_cach_level2(te,c2,m);
        }
     }
     else{
        cout << "==============================Write miss on L2============================\n";
        cout << "==============================Need to alocate from memory to L1 L2=================\n";
        memoryBlock* mb=m.findBlock(tag,blockNum);
        mb->data[wordOffset].s=toWrite;
        CacheBlock temporary;
        cout << "=============================Wrote updated data in memory=======================\n";
        for(int i=0;i<blockSize;i++){
            temporary.data[i]=mb->data[i];
        }
        temporary.isDirty=0;
        temporary.memBlockNum=mb->blockNum;
        temporary.tag=mb->tag;
        temporary.valid_bit=1;
        CacheBlock tff=c2.setBlock(temporary);
        if(tff.isDirty && tff.valid_bit){
            cout << "===========================Dirty Block detected in L2==========================\n";
            cout << "===========================Write Back block " << tff.memBlockNum << " to Memory======================\n";
            manageDirtyBlock_memory(tff,m);
        }
        cout << "===========================Alocated from memory to L2==================\n";
        tff=c1.setBlock(temporary);
        if(tff.isDirty && tff.valid_bit){
            cout << "=============================Dirty block detected in L1=====================\n";
            cout << "=============================Write back block " << tff.memBlockNum<< " to L2 cache\n"; 
            manageDirtyBlock_cach_level2(tff,c2,m);
        } 
    }
   }   
}
void cachController::manageAllDirtyBlock(cache_Level_one &c1,cache_Level_two &c2,memory &m){
    for(int i=0;i<L1cacheSize;i++){
        if(c1.getStorage(i).valid_bit && c1.getStorage(i).isDirty){
            manageDirtyBlock_cach_level2(c1.getStorage(i),c2,m);
        }
    }
    for(int i=0;i<L2CashAssociativity;i++){
        for(int j=0;j<L2CashGroupSize;j++){
            if(c2.getStorage(i,j).valid_bit && c2.getStorage(i,j).isDirty){
                manageDirtyBlock_memory(c2.getStorage(i,j),m);
            }
        }
    }
}
