#ifndef __PAYLOAD_ENTRY_HPP__
#define __PAYLOAD_ENTRY_HPP__

#include <iostream>
#include "./core.hpp"
#include "./query.hpp"
using namespace std;


class PayloadEntry {
    private:
        QueryID id;
        //unsigned int words_in_query;
        //MatchType type;
        //unsigned int dist;
        bool * active;//points to bool of original query
    public:
        PayloadEntry(QueryID, bool *);
        PayloadEntry(int);
        PayloadEntry(PayloadEntry &);
        PayloadEntry();
        ~PayloadEntry();
        void setPayloadEntry(QueryID, bool *);
        QueryID getId();
        bool getActive();
        friend ostream & operator<<(ostream &, const PayloadEntry &);
        bool operator==(PayloadEntry &);
};

#endif
