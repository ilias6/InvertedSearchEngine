#include <iostream>
#include <cstring>
#include "../include/query.hpp"
#include "../include/core.hpp"
#include "../include/hash_table.hpp"
#include "../include/hash_functions.hpp"
#include <fstream>
#include <cstring>
#include <cerrno>
#include "../include/utils.hpp"

using namespace std;

Query::Query(QueryID id, const char * str, MatchType type, unsigned int dist) {
    this->id = id;
    this->type = type;
    this->active = true;
    this->matchDist = dist;
    this->wordsInQuery;
    char buff[100];
    sscanf(str,"%s",buff);
    this->wordsInQuery=atoi(buff);
    if(this->wordsInQuery>MAX_QUERY_WORDS){
        cerr<<"Query contains more words than "<<MAX_QUERY_WORDS<<endl;
        exit(-1);
    }else if(this->wordsInQuery<=0){
        cerr<<"Query size can't be equal or smaller than zero (QueryID "<<this->id<<")"<<endl;
        exit(-1);
    }
    int len=strlen(buff);
    int ret=scan(this->wordsInQuery,str+len,&this->words,&this->wordsInQuery,MAX_WORD_LENGTH,MIN_WORD_LENGTH);
    if(ret==-1){
        cerr<<"Query contains words bigger than "<<MAX_WORD_LENGTH<<endl;
        exit(-1);
    }else if(ret==-2){
        cerr<<"Query file corrupted "<<endl;
        exit(-2);
    }else if(ret==-3){
        cerr<<"Query contains words smaller than "<<MIN_WORD_LENGTH<<endl;
        exit(-1);
    }
}

Query::~Query(){
    for(int i=0;i<wordsInQuery;i++)
	   delete this->words[i];
    delete[] this->words;
}

QueryID Query::getId(){
    return this->id;
}

int Query::getWordsInQuery(){
    return this->wordsInQuery;
}

Word * Query::getWord(int indx){
    if(indx<this->wordsInQuery){
	return words[indx];
    }
    return NULL;
}

MatchType Query::getType() {
    return this->type;
}

unsigned int Query::getMatchDist() {
    return this->matchDist;
}

bool Query::getActive(){
    return this->active;
}

bool * Query::getAdressOfActive(){
    return &active;
}


void Query::activate(){
    this->active=true;
}

void Query::deactivate(){
    this->active=false;
}

void Query::print(){
    cout<<"------------------------"<<endl;
    cout<<"Id: "<<this->id<<endl;
    cout<<"Match type: "<<this->type<<endl;
    cout<<"Match distance: "<<this->matchDist<<endl;
    cout<<"WordsInQuery: "<<wordsInQuery<<endl;
    for(int i=0;i<wordsInQuery;i++)
	cout<<"\t"<<*words[i]<<" "<<words[i]->getLen()<<endl;

    return ;
}
