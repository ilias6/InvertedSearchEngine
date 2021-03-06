#ifndef __HASH_TABLE_HPP__
#define __HASH_TABLE_HPP__
#include "list.hpp"
#include "word.hpp"
#include "entry.hpp"
#include "hash_functions.hpp"

enum HashTableErrorCode{H_T_SUCCESS, H_T_FAIL};
class Bucket{
    private:
        Vector<Entry*> list; //list of Data
    public:
        Bucket();
        // ~Bucket();
        int bucketSize();
        Bucket(Bucket &);
        void copyBucket(Bucket &);
        Vector<Entry *> getListCopy();
        Entry * getEntry(Word *);
        Entry * getEntry(int);
        enum HashTableErrorCode insert(Entry *);
        void print(void);
        void printAddr();
};

class HashTable {
    private:
        int size;
        int current_size;
        Bucket * array;
        unsigned long(*hash_func)(const char *);//pointer to hash function
        void rehash();
    public:
        HashTable();
        HashTable(HashTable &);
        HashTable(int sz,unsigned long (*h_f)(const char *));
        ~HashTable();
        int getSize(void);
        enum HashTableErrorCode setSizeAndAlloc(int s);
        enum HashTableErrorCode setHashFunc(unsigned long (*h_f)(const char * ));
        enum HashTableErrorCode updateEntryPayload(Word *, PayloadEntry &, MatchType, unsigned int dist = 0);
        enum HashTableErrorCode insert(Entry *);
        Bucket getBucketCopy(Word *);
        Entry* getEntry(Word *);
        void print(void);
        void printAddr();
        void deleteData();
};

#endif
