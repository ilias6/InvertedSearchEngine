#include <iostream>
#include <cstring>
#include "../include/entry.hpp"
#include "../include/list.hpp"
#include "../include/word.hpp"

using namespace std;
//val is query id
// and may be used as doc id
Entry::Entry(const char * w, int val):
    word(w), payload() {
    this->addToPayload(val);
}

Entry::Entry(Entry & e):
    word(e.getWord()), payload(e.payload) {}

Entry::~Entry() {}

Entry::Entry(Word & w, int val):word(w),payload() {
    this->addToPayload(val);
}

Word &Entry::getWord() {
    return this->word;
}

List<int> & Entry::getPayload() {
    return this->payload;
}

ListErrorCode Entry::addToPayload(int q) {
    return this->payload.insert(q);
}

ListErrorCode Entry::removeFromPayload(int q) {
    return this->payload.remove(q);
}
//equal operator just check exactMatch of words
bool Entry::operator==(Entry & e) {
    if (this->word.exactMatch(e.getWord()))
	   return true;
    return false;
}

ostream & operator<<(ostream & os, const Entry & e) {
    os << e.word;
    os << " exists in [";
    int l = e.payload.getLen();
    if (l > 0)
    	os << e.payload.getItem(0);
    for (int i = 1; i < l; i++)
        os << ", " << e.payload.getItem(i);
    os << "]";
    return os;
}
