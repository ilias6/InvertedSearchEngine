#include <iostream>
#include <cstring>
#include "../include/payload_entry.hpp"

using namespace std;

PayloadEntry::PayloadEntry(QueryID id, MatchType type, unsigned int dist) {
    this->id = id;
    this->type = type;
    this->dist = dist;
}

PayloadEntry::PayloadEntry(PayloadEntry & pE) {
    this->id = pE.id;
    this->type = pE.type;
    this->dist = pE.dist;
}

PayloadEntry::~PayloadEntry() {}

QueryID PayloadEntry::getID() {
    return this->id;
}

MatchType PayloadEntry::getType() {
    return this->type;
}

unsigned int PayloadEntry::getDist() {
    return this->dist;
}

ostream & operator<<(ostream & os, const PayloadEntry & pE) {
    cout << "QueryID: " << pE.id << " MatchType: " << pE.type << " Dist: " << pE.dist << endl;
    return os;
}

bool PayloadEntry::operator==(PayloadEntry & pE) {
    if (this->id == pE.id)
	return true;
    return false;

}

