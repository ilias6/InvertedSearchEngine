#include "../include/hash_functions.hpp"
/*

    SOURCE : http://www.cse.yorku.ca/~oz/hash.html
                            */
//djb2 hash
unsigned long djb2(const char *str)
    {
        unsigned long hash = 5381;
        int c;

        while ((c = *str++))
            hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

        return hash;
    }
//sdbm hash
unsigned long sdbm(const char*str)
    {

        unsigned long hash = 0;
        int c;

        while ((c = *str++))
            hash = c + (hash << 6) + (hash << 16) - hash;

        return hash;
    }
// lose lose
unsigned long lose_lose(const char *str){
    	unsigned int hash = 0;
    	int c;

    	while ((c = *str++))
    	    hash += c;

    	return hash;
    }
