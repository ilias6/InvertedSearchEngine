#include <iostream>
#include <cstring>
#include "../include/payload_entry.hpp"

using namespace std;

PayloadEntry::PayloadEntry(QueryID id,bool *active){
    this->id=id;
    this->active=active;
}

PayloadEntry::PayloadEntry(int id){
    this->id=id;
}

PayloadEntry::PayloadEntry(){
    this->id=-1;
    this->active=NULL;
}

PayloadEntry::PayloadEntry(PayloadEntry & pE) {
    this->id=pE.id;
    this->active=pE.active;
}

void PayloadEntry::setPayloadEntry(QueryID id,bool *active){
    this->id=id;
    this->active=active;
}


PayloadEntry::~PayloadEntry() {}

QueryID PayloadEntry::getId() {
    return this->id;
}

bool PayloadEntry::getActive(){
    return *this->active;
}

ostream & operator<<(ostream & os, const PayloadEntry & pE) {
    cout << "QueryID: " << pE.id <<" Active: "<<*pE.active << endl;
    return os;
}

bool PayloadEntry::operator==(PayloadEntry & pE) {
    if (this->id == pE.id)
        return true;
    return false;

}
