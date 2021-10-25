#include <iostream>
#include <cstring>
#include "../include/entry.hpp"
#include "../include/list.hpp"
#include "../include/word.hpp"


Entry::Entry(const char * w, int val):
    word(w), payload() {
    this->addToPayload(val);
}

Word &Entry::getWord(){
    return this->word;
}

List<int> Entry::getPayload() {
    return this->payload;
}

void Entry::addToPayload(int q) {
    this->payload.insert(q);
}

bool Entry::operator==(Entry & e) {
   if (this->word.exactMatch(e.getWord()))
	return true;
    return false;
}
