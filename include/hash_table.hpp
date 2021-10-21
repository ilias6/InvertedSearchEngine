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
        enum htable_retval insert(Entry *);
        void print(void);
};

class HashTable {
    private:
        int size;
        Bucket * array;
        long long (*hash_func)(Word & w);//pointer to hash function
    public:
        HashTable();
        HashTable(int sz,long long (*)(Word &));
        ~HashTable();
        int getSize(void);
        void setSize(int s);
        void setHashFunc(long long (*)(Word &))
        enum htable_retval insert(Word & w);
        int getEntry(Word &w);


};

#endif
