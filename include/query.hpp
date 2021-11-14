#ifndef __QUERY_HPP__
#define __QUERY_HPP__


#include "../include/word.hpp"
#include "../include/vector.hpp"
#include "../include/core.hpp"
#define MAX_QUERY_LENGTH ((MAX_WORD_LENGTH+1)*MAX_QUERY_WORDS)

class Query{
    private:
        Word ** word;
        int id;
        int wordsInQuery;
        char * queryPath;
        //MatchType type;
        //bool active;
        //unsigned int matchDist;
   public:
        //static long int lastCharRead = 0;
        Query(int, const char *);
        //Query(int, Vector<char> &, int);
        Query();
        ~Query();
        int getId();
        int getWordsInQuery();
        Word * getWord(int);
        void print();

};

#endif
