#include <iostream>
#include <cstring>
#include "../include/document.hpp"
#include "../include/core.h"
#include "../include/hash_table.hpp"
#include "../include/hash_functions.hpp"
#include <fstream>
#include <cstring>
#include <cerrno>
#include "../include/utils.hpp"

using namespace std;

Document::Document(DocID id, const char * str) {
    this->id = id;
    this->wordsInDoc = countSpaces(str)+1;
    if(this->wordsInDoc<=0){
        cerr<<"Document size can't be equal or smaller than zero (DocID "<<this->id<<")"<<endl;
        exit(-1);
    }
    int ret=scan(this->wordsInDoc,str,&this->words,&this->wordsInDoc,MAX_WORD_LENGTH,MIN_WORD_LENGTH);
    if(ret==-1){
        cerr<<"Doc contains words bigger than "<<MAX_WORD_LENGTH<<endl;
        exit(-1);
    }else if(ret==-2){
        cerr<<"Doc file corrupted "<<endl;
        exit(-2);
    }else if(ret==-3){
        cerr<<"Doc contains words smaller than "<<MIN_WORD_LENGTH<<endl;
        exit(-1);
    }
}
Document::~Document(){
    for(int i=0;i<wordsInDoc;i++)
        delete this->words[i];
    delete[] this->words;
}
DocID Document::getId(){
    return this->id;
}
int Document::getWordsInDoc(){
    return wordsInDoc;
}

Word *Document::getWord(int indx){
    if(indx<this->wordsInDoc){
        return words[indx];
    }
    return NULL;
}


void Document::print(){
    cout<<"------------------------"<<endl;
    cout<<"Id: "<<this->id<<endl;
    cout<<"WordsInDoc: "<<wordsInDoc<<endl;
    for(int i=0;i<wordsInDoc;i++)
        cout<<"\t"<<*words[i]<<" "<<words[i]->getLen()<<endl;

    return ;
}
