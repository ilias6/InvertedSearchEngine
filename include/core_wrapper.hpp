#ifndef __CORE_WRAPPER_HPP__
#define __CORE_WRAPPER_HPP__

#include "hash_table.hpp"
#include "entry_list.hpp"
#include "index.hpp"
#include "list.hpp"
#include "entry.hpp"
#include "word.hpp"
#include "query.hpp"

#define MAX_DISTANCES MAX_WORD_LENGTH-MIN_WORD_LENGTH

class CoreWrapper {
    private:
        unsigned int queryCounter;
        unsigned int Q;
        EntryList * entryList;

        //		      Index ***
        //    	     	  	|
        //       	Index * [3] (MatchType)

        /* Index[0] has size=1 and is an exact match index --> a hash table */
        /* For the other two index pointers: */
        /* We define Max_possible_distances=Max_word_length - Min_word_length.
           So for i=1,2 we have: Index[i][Max_possible_distances] */
        Index *** indeces;
        Query ** queries;
        //Document ** docs;
    public:
	CoreWrapper(unsigned int);
	~CoreWrapper();
	IndexErrorCode addQuery(QueryID, const char *, MatchType, unsigned int);
};

#endif
