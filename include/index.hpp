#ifndef __INDEX_HPP__
#define __INDEX_HPP__

#include "BK_tree.hpp"
#include "entry.hpp"
#include "hash_table.hpp"
#include "entry_list.hpp"
#include "core.hpp"
#include "word.hpp"

using namespace std;

class Index {
    private:
        MatchType type;
        BKTree *tree;
	    HashTable *hTable;
        void insertFromList(EntryList &);
    public:
        Index(EntryList &,MatchType);
        List<Entry *> search(Word *, int n = 0);
        ~Index();
};



#endif
