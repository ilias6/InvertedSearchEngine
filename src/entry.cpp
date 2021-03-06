#include <iostream>
#include <cstring>
#include "../include/entry.hpp"
#include "../include/list.hpp"
#include "../include/word.hpp"

using namespace std;


//val is query id
// and may be used as doc id
Entry::Entry(const char * w, PayloadEntry & pEntry, MatchType mt, unsigned int dist):
    word(w) {
        this->addToPayload(pEntry, mt, dist);
    }

Entry::Entry(Entry & e):
    word(e.getWord()), payload(e.payload) {}


Entry::~Entry() {}

Entry::Entry(Word & w, PayloadEntry & pEntry, MatchType mt, unsigned int dist):
        word(w) {
            this->addToPayload(pEntry, mt, dist);
        }

Word &Entry::getWord() {
    return this->word;
}

List<PayloadEntry> & Entry::getPayload(MatchType mt, unsigned int dist) {
    return this->payload[mt][dist];
}

ListErrorCode Entry::addToPayload(PayloadEntry & pEntry, MatchType mt, unsigned int dist) {
    if (mt == MT_EXACT_MATCH)
        return this->payload[0][0].insert(pEntry);

    if (dist > MAX_DISTANCE)
        return L_FAIL;

    if (mt == MT_HAMMING_DIST)
        return this->payload[1][dist].insert(pEntry);
    
    if (mt == MT_EDIT_DIST)
        return this->payload[2][dist].insert(pEntry);

    return L_FAIL;
}

/*
ListErrorCode Entry::removeFromPayload(PayloadEntry & pEntry) {
    return this->payload.remove(pEntry);
}

*/

//equal operator just check exactMatch of words
bool Entry::operator==(Entry & e) {
    if (this->word.exactMatch(e.getWord()))
        return true;
    return false;
}

ostream & operator<<(ostream & os, const Entry & e) {
    /*os << e.word;
    os << " exists in [";
    int l = e.payload.getLen();
    if (l > 0)
        os << e.payload.getItem(0);
    for (int i = 1; i < l; i++)
        os << ", " << e.payload.getItem(i);
    os << "]";
    */
    return os;
}
