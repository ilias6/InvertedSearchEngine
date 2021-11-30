#include <iostream>
#include <cstring>
#include "../include/payload_entry.hpp"

using namespace std;

PayloadEntry::PayloadEntry(QueryID id,unsigned int words,MatchType type,unsigned int dist,bool *active){
    this->id=id;
    this->words_in_query=words;
    this->type=type;
    this->dist=dist;
    this->active=active;
}

PayloadEntry::PayloadEntry(PayloadEntry & pE) {
    this->id=pE.id;
    this->words_in_query=pE.words_in_query;
    this->type=pE.type;
    this->dist=pE.dist;
    this->active=pE.active;
}

PayloadEntry::~PayloadEntry() {}

unsigned int PayloadEntry::getWordsInQuery(){
    return this->words_in_query;
}

QueryID PayloadEntry::getId() {
    return this->id;
}

MatchType PayloadEntry::getType() {
    return this->type;
}

unsigned int PayloadEntry::getDist() {
    return this->dist;
}

bool PayloadEntry::getActive(){
    return *this->active;
}

ostream & operator<<(ostream & os, const PayloadEntry & pE) {
    cout << "QueryID: " << pE.id << " MatchType: " << pE.type << " Dist: " << pE.type <<" Active: "<<*pE.active << endl;
    return os;
}

bool PayloadEntry::operator==(PayloadEntry & pE) {
    if (this->id == pE.id)
	   return true;
    return false;

}