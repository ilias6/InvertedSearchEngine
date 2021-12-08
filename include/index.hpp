#ifndef __INDEX_HPP__
#define __INDEX_HPP__

#include "BK_tree.hpp"
#include "entry.hpp"
#include "hash_table.hpp"
#include "entry_list.hpp"
#include "core.h"
#include "word.hpp"

using namespace std;

enum IndexErrorCode {I_SUCCESS, I_FAIL};

class Index {
    private:
        MatchType type;
        int numOfTrees;//will be 1 if we have edit distance
        BKTree **tree;
        HashTable *hTable;
        IndexErrorCode insert(Entry *);
    public:
        MatchType getType();
        Index(MatchType,int);
        IndexErrorCode insert(Entry **);//NULL terminated array of Entry **
        List<Entry *> search(Word *, int n = 0);
        ~Index();
};


#endif
