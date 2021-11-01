#ifndef __ENTRY_LIST_HPP__
#define __ENTRY_LIST_HPP__
#include "hash_table.hpp"
#include "list.hpp"
#include "entry.hpp"
#include "word.hpp"
#include "query.hpp"

class EntryList{
    private:
        HashTable hashtable;
        List<Entry> list;
        int insert(Word *,int);
        int remove(Word *,int);
    public:
        EntryList();
        ~EntryList();
        int insert(Query &);
        Entry * getItemPtr(int);
        int remove(Query &);
        HashTable & getHashTable();
        int getLen();
        void print();

};

#endif
