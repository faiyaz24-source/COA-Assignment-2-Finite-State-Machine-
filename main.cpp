#include<bits/stdc++.h>
#include "cache.h"
#include "cache_level_one.h"
#include "cache_level_two.h"
#include "memory.h"
#include "cachController.h"
using namespace std;
int main(){
    memory m;
    cache_Level_one c1;
    cache_Level_two c2;
    cachController control;
    while(1){
       int request;
       cout << "===================Idle State===============\n";
       cout << "Give request:\n1.Read\n2.Write\n3.Shut Down PC" << endl;
       cout << "Request: ";
       cin >> request;
       if(request==3){
           break;
       }
       if(request!=2 && request!=1){
           cout << "Invalid Command" << endl;
           continue;
       }
       cout << "===================Compare Tag===============\n";
       int blockNum,wordOffset;
          string tag;
          cout << "Enter Memory Block Num:(0-99)";
          cin >> blockNum;
          cout << "Enter word Offset:(0-3)";
          cin >> wordOffset;
          tag=to_string(blockNum);
       if(request==1){
          string word=control.readWord(blockNum,tag,wordOffset,c1,c2,m);
          cout <<"OutPut: "<<word << endl;
        }
        if(request==2){
               string input;
               cout << "Word to be  written: ";
               cin >> input;
               control.writeWord(blockNum,tag,wordOffset,input,c1,c2,m); 
        }
        cout << "Show cach Level 1 Status(y/n): ";
          char dis;
          cin >> dis;
          if(dis=='y'){
             c1.printCachStatus();
          }
          cout << "Show cach Level 2 Status(y/n): ";
          cin >> dis;
          if(dis=='y'){
             c2.printStatus();
          }
          cout << "Show recently accessed memory block(y/n): ";
          cin >> dis;
          if(dis=='y'){
            m.printMemoryStatus(blockNum);
          }
    }
    cout << "=====================Resolving all dirty blocks and shutting down===========================\n";
    control.manageAllDirtyBlock(c1,c2,m);
    return 0;
}