#ifndef __HASH_TABLE_HPP__
#define __HASH_TABLE_HPP__
#include "list.hpp"
#include "word.hpp"
#include "entry.hpp"

enum htable_retval{SUCCESS,FAILURE};
class Bucket{
    private:
        List<Entry*> list; //list of Data
    public:
        Bucket();
        // ~Bucket();
        int bucketSize();
        bool existsInBucket(Entry *);
        Entry * getEntry(Entry *);
        enum htable_retval insert(Entry *);
        void print(void);
};

class HashTable {
    private:
        int size;
        Bucket * array;
        unsigned long(*hash_func)(const char *);//pointer to hash function
    public:
        HashTable();
        HashTable(int sz,unsigned long (*)(const char *));
        ~HashTable();
        int getSize(void);
        void setSize(int s);
        void setHashFunc(unsigned long (*)(const char * ));
        enum htable_retval updateEntryPayload(Entry *,int);
        enum htable_retval insert(Entry *);
        int getEntry(Entry *);


};

#endif
