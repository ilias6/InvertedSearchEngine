#ifndef __HASH_TABLE_QUERY_HPP__
#define __HASH_TABLE_QUERY_HPP__
#include "list.hpp"
#include "query_entry.hpp"
#include "hash_functions.hpp"

enum HashTableQueryErrorCode{H_T_Q_SUCCESS, H_T_Q_FAIL};

class BucketQuery{
    private:
        Vector<QueryEntry *> list; //list of Data
    public:
        BucketQuery();
        // ~BucketQuery();
        int bucketSize();
        BucketQuery(BucketQuery &);
        void copyBucketQuery(BucketQuery &);
        Vector<QueryEntry *> getListCopy();
        Vector<QueryEntry *> * getList();
        QueryEntry * getQueryEntry(QueryID, bool);
        enum HashTableQueryErrorCode insert(QueryEntry *);
        void print(void);
        void printAddr();
};

class HashTableQuery {
    private:
        int size;
        int current_size;
        BucketQuery * array;
        unsigned long(*hash_func)(const char *);//pointer to hash function
        void rehash();
    public:
        HashTableQuery();
        HashTableQuery(HashTableQuery &);
        HashTableQuery(int sz,unsigned long (*h_f)(const char *));
        ~HashTableQuery();
        int getSize(void);
        int getNumOfQueries(void);
        enum HashTableQueryErrorCode setSizeAndAlloc(int s);
        enum HashTableQueryErrorCode setHashFunc(unsigned long (*h_f)(const char * ));
        enum HashTableQueryErrorCode insert(QueryEntry *);
        BucketQuery * getBucket(int);
        QueryEntry * getQueryEntry(QueryID);
        void print(void);
        void printAddr();
        void deleteData();
};

#endif
