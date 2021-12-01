#ifndef __QUERY_HPP__
#define __QUERY_HPP__


#include "../include/word.hpp"
#include "../include/vector.hpp"
#include "../include/core.hpp"

class Query{
    private:
        //char * queryPath;

        Word ** words;
        QueryID id;
        int wordsInQuery;
        MatchType type;
        bool active;
        unsigned int matchDist;
   public:
        // Query(int, const char *);
        Query(QueryID, const char *, MatchType, unsigned int dist = 0);
        Query();
        ~Query();
        QueryID getId();
        int getWordsInQuery();
        Word * getWord(int);
        MatchType getType();
        unsigned int getMatchDist();
        bool getActive();
        void Activate();
        void Deactivate();
        void print();
        bool * getAdressOfActive();

};

#endif
