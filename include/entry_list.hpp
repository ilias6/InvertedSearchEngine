#ifndef __ENTRY_LIST_HPP__
#define __ENTRY_LIST_HPP__

#include "hash_table.hpp"
#include "list.hpp"
#include "entry.hpp"
#include "word.hpp"
#include "query.hpp"

enum EntryListErrorCode {E_L_SUCCESS, E_L_FAIL};

class EntryList{
    private:
        HashTable hashtable;
        List<Entry> list;

        EntryListErrorCode insert(Word *,  PayloadEntry &, MatchType, unsigned int,Entry **);
        EntryListErrorCode remove(Word *, int);
    public:
        EntryList(int n = 97);
        ~EntryList();
        EntryListErrorCode insert(Query &, Entry ***);
        EntryListErrorCode remove(Query &);
        Entry * getItemPtr(int);
        HashTable & getHashTable();
        int getLen();
        void print();

};

#endif
