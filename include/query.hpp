#ifndef __QUERY_HPP__
#define __QUERY_HPP__

#include "../include/word.hpp"

class Query{
    private:
        Word ** word;
        int id;
        char * queryPath;
        int wordsInQuery;
   public:
        Query(int, const char *);
        Query();
        ~Query();
        int getId();
        int getWordsInQuery();
        Word * getWord(int);
        void print();

};

#endif
