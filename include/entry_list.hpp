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
        EntryListErrorCode insert(Word *,int);
        EntryListErrorCode remove(Word *,int);
    public:
        EntryList();
        ~EntryList();
        EntryListErrorCode insert(Query &);
        Entry * getItemPtr(int);
        EntryListErrorCode remove(Query &);
        HashTable & getHashTable();
        int getLen();
        void print();

};

#endif
