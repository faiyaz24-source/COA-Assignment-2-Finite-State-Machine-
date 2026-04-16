#include "memory.h"

string memory::serialize(memoryBlock b){
    string s;
    s=to_string(b.blockNum)+"*"+b.tag+"*";
    for(int i=0;i<blockSize;i++){
        s+=(b.data[i].s+"*");
    }
    return s;
}
memoryBlock memory::deserialize(string s){
    int i=0;
    string temp="";
    memoryBlock mb;
    for(;s[i]!='*';i++){
        temp+=s[i];
    }
    mb.blockNum=stoi(temp);
    i++;
    temp="";
    for(;s[i]!='*';i++){
        temp+=s[i];
    }
    mb.tag=temp;
    i++;
    for(int j=0;j<blockSize;j++){
        temp="";
        while(s[i]!='*'){
           temp+=s[i];
           i++;
        }
        i++;
        mb.data[j].s=temp;
    }
    return mb;
}
memory::memory(){
    ifstream file("memory.txt");
    int i=0;
    string s;
    while(i<memorySize && getline(file,s)){
        storage[i]=deserialize(s);
        i++;
    }
    file.close();
}
memory::~memory(){
    ofstream file("memory.txt");
    string s;
    for(int i=0;i<memorySize;i++){
        s=serialize(storage[i]);
        file << s << endl;
    }
    file.close();
}
memoryBlock* memory::findBlock(string tag,int blockNum){
    return &storage[blockNum];
}
void memory::updateBlock(CacheBlock cb){
    memoryBlock mb;
    mb.blockNum=cb.memBlockNum;
    mb.tag=cb.tag;
    for(int i=0;i<blockSize;i++){
        mb.data[i]=cb.data[i];
    } 
    storage[cb.memBlockNum]=mb;
}
void memory::printMemoryStatus(int memBlockNum){
    cout << "Block_Num: " << memBlockNum << endl;
    for(int i=0;i<blockSize;i++){
         cout << "Word offset: "<< i << " word: " << storage[memBlockNum].data[i].s << endl;
    }
    cout << "\n";
}
void memory::printFullMemory(){
    for(int i=0;i<memorySize;i++){
        printMemoryStatus(i);
    }
}