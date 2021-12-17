#ifndef __ENTRY_HPP__
#define __ENTRY_HPP__

#include <iostream>
#include "./word.hpp"
#include "./payload_entry.hpp"
#include "./list.hpp"
using namespace std;
#define MAX_DISTANCE 3

#define MATCH_TYPES_NUM 3
#define MAX_DISTANCE 3

class Entry {
    private:
        Word word;
		Word * wPtr;
        List<PayloadEntry> payload[MATCH_TYPES_NUM+1][MAX_DISTANCE];
		// int idx;
    public:
        List<PayloadEntry> & getPayload(MatchType, unsigned int dist=0);
        ListErrorCode addToPayload(PayloadEntry &, MatchType, unsigned int);
        // ListErrorCode removeFromPayload(PayloadEntry &);
        Word &getWord();
        Entry(const char *, PayloadEntry &, MatchType, unsigned int);
        Entry(Word &, PayloadEntry &, MatchType, unsigned int);
        Entry(Entry &);
        ~Entry();
        friend ostream & operator<<(ostream &, const Entry &);
        bool operator==(Entry &);
};

#endif
