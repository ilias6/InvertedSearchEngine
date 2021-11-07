#ifndef __ENTRY_LIST_HPP__
#define __ENTRY_LIST_HPP__
#include "hash_table.hpp"
#include "list.hpp"
#include "entry.hpp"
#include "word.hpp"
#include "query.hpp"

enum entryListErrorCode {SUCCESS, FAIL}

class EntryList{
    private:
        HashTable hashtable;
        List<Entry> list;
        entryListErrorCode insert(Word *,int);
        entryListErrorCode remove(Word *,int);
    public:
        EntryList();
        ~EntryList();
        entryListErrorCode insert(Query &);
        Entry * getItemPtr(int);
        entryListErrorCode remove(Query &);
        HashTable & getHashTable();
        int getLen();
        void print();

};

#endif
