#ifndef __DOCUMENT_HPP__
#define __DOCUMENT_HPP__

#include "../include/word.hpp"

class Document {
    private:
	       Word ** word;
           int id;
           char * docPath;
	       int wordsInDoc;
    public:
	       Document(int, const char *);
	      ~Document();
          int getId();
          int getWordsInDoc();
          Word * getWord(int);
          void print();
};




#endif
