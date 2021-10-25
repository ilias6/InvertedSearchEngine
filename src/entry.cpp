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

Entry::Entry(Word &w,int val):word(w),payload(){
    this->addToPayload(val);
}


void Entry::print(void){
    this->word.print();
    cout<<" exists in [";
    int l=payload.getLen();
    cout<<payload.getItem(0);
    for(int i=1;i<l;i++)
        cout<<","<<payload.getItem(i);
    cout<<"]";
    return ;
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
