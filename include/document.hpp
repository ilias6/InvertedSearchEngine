#ifndef __DOCUMENT_HPP__
#define __DOCUMENT_HPP__

#include "./word.hpp"

class Document {
    private:
	Word * doc;
	HashTable hashTable;
	int id;
	int cSize;
	int wSize;
    public:
	Document(int, char *);
	~Document();
	int getId();
	int getWSize();
	int getCSize();
	Word * getWord(int);
}




#endif

