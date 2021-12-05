#ifndef __CORE_WRAPPER_HPP__
#define __CORE_WRAPPER_HPP__

#include "hash_table.hpp"
#include "entry_list.hpp"
#include "index.hpp"
#include "list.hpp"
#include "entry.hpp"
#include "word.hpp"
#include "query.hpp"
#include "document.hpp"
#include "result.hpp"
#include "queue.hpp"


#define MAX_DISTANCES MAX_WORD_LENGTH-MIN_WORD_LENGTH
enum CoreWrapperErrorCode {C_W_SUCCESS,C_W_FAIL};
class CoreWrapper {
    private:
        EntryList * entryList;

        //		      Index ***
        //    	     	  	|
        //       	Index * [3] (MatchType)

        /* Index[0] has size=1 and is an exact match index --> a hash table */
        /* For the other two index pointers: */
        /* We define Max_possible_distances=Max_word_length - Min_word_length.
           So for i=1,2 we have: Index[i][Max_possible_distances] */
        Index *** indeces;
        Vector<Query*> * queries;
        Queue<Document *> * docs;
        Queue<Result *> * results;

        void increaseCounter(List<Entry *>&,Result *,MatchType,unsigned int dist=0);
        void searchWordInIndeces(Word *,Result *);
    public:
	CoreWrapper();
	~CoreWrapper();
	CoreWrapperErrorCode addQuery(QueryID, const char *, MatchType, unsigned int);
	CoreWrapperErrorCode deactivateQuery(QueryID);
    CoreWrapperErrorCode addDocument(DocID,const char *);
    Document *pullDocument();
    Result * matchDocument(Document *);
    CoreWrapperErrorCode addResult(Result *);
    Result *pullResult();

};

#endif
