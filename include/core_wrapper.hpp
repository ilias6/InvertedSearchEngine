#ifndef __CORE_WRAPPER_HPP__
#define __CORE_WRAPPER_HPP__

#include "hash_table_query.hpp"
#include "entry_list.hpp"
#include "index.hpp"
#include "list.hpp"
#include "entry.hpp"
#include "word.hpp"
#include "query.hpp"
#include "document.hpp"
#include "result.hpp"
#include "queue.hpp"
#include "scheduler.hpp"
#include <pthread.h>

#define MAX_DISTANCES MAX_WORD_LENGTH-MIN_WORD_LENGTH
enum CoreWrapperErrorCode {C_W_SUCCESS,C_W_FAIL};
class CoreWrapper {
    private:
    public:
        CoreWrapper();
        ~CoreWrapper();
        CoreWrapperErrorCode addQuery(QueryID, const char *, MatchType, unsigned int);
        CoreWrapperErrorCode deactivateQuery(QueryID);
        CoreWrapperErrorCode addDocument(DocID,const char *);
        Document *pullDocument();
        CoreWrapperErrorCode matchDocument(Document *);
        CoreWrapperErrorCode addResult(Result *);
        Result *pullResult();


        void increaseCounter(List<Entry *>&,Result *,MatchType,unsigned int dist);
        void increaseCounter(List<Entry *>&,Result *);
        // void searchWordInIndeces(Word *,Result *, int);
        void searchWordExact(Document *,Result *, int);
        void searchWordEdit(Document *,Result *, int);
        void searchWordHamm(Document *,Result *, int);
        void searchWordHammAndExact(Document *,Result *, int);

        EntryList * entryList;

        //            Index ***
        //                  |
        //          Index * [3] (MatchType)

        /* Index[0] has size=1 and is an exact match index --> a hash table */
        /* For the other two index pointers: */
        /* We define Max_possible_distances=Max_word_length - Min_word_length.
           So for i=1,2 we have: Index[i][Max_possible_distances] */
        Index *** indeces;
        Vector<Query*> * queries;
        // HashTableQuery * queries;
        Queue<Document *> * docs;
        Queue<Result *> * results;
        //HashTable * exactEntries;

        Scheduler * scheduler;
};

#endif
