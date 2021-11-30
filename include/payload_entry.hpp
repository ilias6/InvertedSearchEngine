#ifndef __PAYLOAD_ENTRY_HPP__
#define __PAYLOAD_ENTRY_HPP__

#include <iostream>
#include "./core.hpp"
using namespace std;

class PayloadEntry {
    private:
	QueryID id;
	MatchType type;
	unsigned int dist;
    public:
        PayloadEntry(QueryID, MatchType,unsigned int);
        PayloadEntry(PayloadEntry &);
        ~PayloadEntry();
	QueryID getID();
	MatchType getType();
	unsigned int getDist();
        friend ostream & operator<<(ostream &, const PayloadEntry &);
        bool operator==(PayloadEntry &);
};

#endif

