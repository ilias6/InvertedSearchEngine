#ifndef __HASH_TABLE_HPP__
#define __HASH_TABLE_HPP__
#include "list.hpp"
#include "word.hpp"
#include "entry.hpp"

enum HashTabelErrorCode{H_T_SUCCESS, H_T_FAIL};
class Bucket{
    private:
        List<Entry*> list; //list of Data
    public:
        Bucket();
        // ~Bucket();
        int bucketSize();
        void copyBucket(Bucket &);
        Entry * getEntry(Word *);
        Entry * getEntry(int);
        enum HashTabelErrorCode insert(Entry *);
        void print(void);
	void printAddr();
};

class HashTable {
    private:
        int size;
        Bucket * array;
        unsigned long(*hash_func)(const char *);//pointer to hash function
    public:
        HashTable();
        HashTable(HashTable &);
        HashTable(int sz,unsigned long (*h_f)(const char *));
        ~HashTable();
        int getSize(void);
        void setSizeAndAlloc(int s);
        void setHashFunc(unsigned long (*h_f)(const char * ));
        enum HashTabelErrorCode updateEntryPayload(Word *,int);
        enum HashTabelErrorCode insert(Entry *);
        Entry* getEntry(Word *);//ultra fail function
        void print(void);
	void printAddr();
        void deleteData();
};

#endif
