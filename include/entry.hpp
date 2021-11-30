#ifndef __ENTRY_HPP__
#define __ENTRY_HPP__

#include <iostream>
#include "./word.hpp"
#include "./payload_entry.hpp"
#include "./list.hpp"
using namespace std;

class Entry {
    private:
        Word word;
        List<PayloadEntry> payload;
    public:
        List<PayloadEntry> & getPayload();
        ListErrorCode addToPayload(PayloadEntry &);
        ListErrorCode removeFromPayload(PayloadEntry &);
        Word &getWord();
        Entry(const char *, PayloadEntry &);
        Entry(Word &, PayloadEntry &);
        Entry(Entry &);
        ~Entry();
        friend ostream & operator<<(ostream &, const Entry &);
        bool operator==(Entry &);
};

#endif
