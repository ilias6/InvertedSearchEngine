#ifndef __HASH_TABLE_HPP__
#define __HASH_TABLE_HPP__
#include "list.hpp"
#include "word.hpp"
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
        unsigned long(*hash_func)(Word & );//pointer to hash function
    public:
        HashTable();
        HashTable(int sz,unsigned long (*)(Word &));
        ~HashTable();
        int getSize(void);
        void setSize(int s);
        void setHashFunc(unsigned long (*)(Word &));
        enum htable_retval updateEntryPayload(Entry *,int);
        enum htable_retval insert(Entry *,int);
        int getEntry(Entry *);


};

#endif
