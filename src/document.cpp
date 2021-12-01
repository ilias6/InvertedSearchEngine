#include <iostream>
#include <cstring>
#include "../include/document.hpp"
#include "../include/core.hpp"
#include "../include/hash_table.hpp"
#include "../include/hash_functions.hpp"
#include <fstream>
#include <cstring>
#include <cerrno>
#include "../include/utils.hpp"

using namespace std;

Document::Document(DocID id, const char * str) {
    this->id = id;

    int strLen = strlen(str);
    int buffIndex = 0;
    int wordsNum = 0;
    char * buff = new char[32];
    Word ** tmp = new Word*[MAX_DOC_WORDS];
    HashTable hashtable(findNextPrime(MAX_DOC_WORDS/128),djb2);
    for (int i = 0; i < strLen; ++i) {
    	if (i < strLen-1 && charInWhitespace(str[i+1]) && charInWhitespace(str[i]))
    	    continue;
    	if (charInWhitespace(str[i]) && buffIndex == 0)
    	    continue;
    	if (charInWhitespace(str[i])) {
    	    buff[buffIndex] = '\0';
    	    Word * w = new Word(buff);

            if(hashtable.getEntry(w)==NULL){
                PayloadEntry p(0,0,MT_EXACT_MATCH,0,NULL);
                Entry * e=new Entry(*w,p);
                hashtable.insert(e);
                //word doesn't already exists
               tmp[wordsNum] = w;
               wordsNum++;
           }else{
               //means Word exists
               delete w;
           }
    	    buffIndex = 0;
    	    continue;
    	}
    	else if (strLen == i+1) {
    	    buff[buffIndex] = str[i];
    	    buff[buffIndex+1] = '\0';
    	    Word * w = new Word(buff);
            if(hashtable.getEntry(w)==NULL){
                PayloadEntry p(0,0,MT_EXACT_MATCH,0,NULL);
                Entry * e=new Entry(*w,p);
                hashtable.insert(e);
                //word doesn't already exists
                tmp[wordsNum] = w;
                wordsNum++;
            }else{
                //means Word exists
                delete w;
            }
            buffIndex = 0;
            continue;
    	}
    	buff[buffIndex] = str[i];
    	buffIndex++;
    }
    hashtable.deleteData();
    delete[] buff;
    this->wordsInDoc = wordsNum;
    if(this->wordsInDoc>MAX_DOC_WORDS){
        cerr << "Doc contains more words than MAX_QUERY_WORDS (" << MAX_DOC_WORDS <<")"<< endl;
        exit(1);
    }
    this->words = new Word*[wordsNum];
    for (int i = 0; i < wordsNum; ++i)
        this->words[i] = tmp[i];
    delete[] tmp;
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
