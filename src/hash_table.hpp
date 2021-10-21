#ifndef __HASH_TABLE_HPP__
#define __HASH_TABLE_HPP__
#include "list.hpp"
#include "word.hpp"
enum htable_retval{SUCCESS,FAILURE};
class Bucket{
    private:
        class Data{
            private:
                Word &word;
                int entry_index;
            public:
                Data(Word &,int);
                Word & getWord(void);
                void setWord(Word &);
                void setEntryIndex(int);
                int GetEntryIndex(void);
                void print(void);
                bool operator==(const Data &);
        };
        List<Data> list; //list of Data
    public:
        Bucket();
        // ~Bucket();
        int bucketSize();
        int getEntryIndex(Word &);//if ret val is -1 -> word doesn't exist
        enum htable_retval insert(Word &,int);
        void print(void);
};

class HashTable {
    private:
        int size;
        Bucket * array;
        long long (*hash_func)(Word & w);//pointer to hash function
    public:
        HashTable();
        ~HashTable();
        int getSize(void);
        int setSize(int s);
        enum htable_retval insert(Word & w);
        int getEntryIndex(Word &w);


};

#endif
