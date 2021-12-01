#ifndef __DOCUMENT_HPP__
#define __DOCUMENT_HPP__

#include "../include/word.hpp"
#include "../include/core.hpp"
#define MAX_DOC_WORDS ((MAX_DOC_LENGTH+1)/MIN_WORD_LENGTH)
class Document {
    private:
	       Word ** words;
           DocID id;
	       int wordsInDoc;
    public:
	       Document(DocID, const char *);
	      ~Document();
          DocID getId();
          int getWordsInDoc();
          Word * getWord(int);
          void print();
};




#endif
