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

    int strLen = strlen(str);
    int buffIndex = 0;
    int wordsNum = 0;
    char * buff = new char[32];
    Word ** tmp = new Word*[MAX_QUERY_WORDS];
    for (int i = 0; i < strLen; ++i) {
	if (i < strLen-1 && charInWhitespace(str[i+1]) && charInWhitespace(str[i]))
	    continue;
	if (charInWhitespace(str[i]) && buffIndex == 0)
	    continue;
	if (charInWhitespace(str[i])) {
	    buff[buffIndex] = '\0';
	    Word * w = new Word(buff);
	    tmp[wordsNum] = w;
	    buffIndex = 0;
	    wordsNum++;
	    continue;
	}
	else if (strLen == i+1) {
	    buff[buffIndex] = str[i];
	    buff[buffIndex+1] = '\0';
	    Word * w = new Word(buff);
	    tmp[wordsNum] = w;
	    buffIndex = 0;
	    wordsNum++;
	    continue;
	}
	buff[buffIndex] = str[i];
	buffIndex++;
    }
    delete[] buff;
    this->wordsInQuery = wordsNum;
    if(this->wordsInQuery>MAX_QUERY_WORDS){
	cerr << "Query contains more words than MAX_QUERY_WORDS (" << MAX_QUERY_WORDS <<")"<< endl;
	exit(1);
    }
    this->words = new Word*[wordsNum];
    for (int i = 0; i < wordsNum; ++i)
	this->words[i] = tmp[i];
    delete[] tmp;
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


void Query::Activate(){
    this->active=true;
}

void Query::Deactivate(){
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
