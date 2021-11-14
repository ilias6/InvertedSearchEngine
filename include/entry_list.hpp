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

        EntryListErrorCode insert(Word *, int);
        EntryListErrorCode remove(Word *, int);
    public:
        EntryList(int);
        ~EntryList();
        EntryListErrorCode insert(Query &);
        EntryListErrorCode remove(Query &);
        Entry * getItemPtr(int);
        //just for unit test
        HashTable & getHashTable();
        int getLen();//return size of list
        void print();

};

#endif
