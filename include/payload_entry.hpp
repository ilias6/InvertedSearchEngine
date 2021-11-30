#ifndef __PAYLOAD_ENTRY_HPP__
#define __PAYLOAD_ENTRY_HPP__

#include <iostream>
#include "./core.hpp"
#include "./query.hpp"
using namespace std;

class PayloadEntry {
    private:
	QueryID id;
    unsigned int words_in_query;
	MatchType type;
	unsigned int dist;
    bool * active;//points to bool of original query
    public:
        PayloadEntry(QueryID,unsigned int,MatchType,unsigned int,bool *);
        PayloadEntry(PayloadEntry &);
        ~PayloadEntry();
	QueryID getId();
	MatchType getType();
	unsigned int getDist();
    unsigned int getWordsInQuery();
    bool getActive();
    friend ostream & operator<<(ostream &, const PayloadEntry &);
    bool operator==(PayloadEntry &);
};

#endif
