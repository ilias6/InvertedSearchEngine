#ifndef __WORD_HPP__
#define __WORD_HPP__

#include <iostream>
using namespace std;

class Word {
    private:
        int len;
        char * str;
    public:
        /*Basic*/
        void set(const char *);
        int getLen();
        const char * getStr();
        friend ostream & operator<<(ostream &, const Word &);
        bool operator==(Word &);
        bool exactMatch(Word &);
        int hammingDist(Word &);
        int editDist(Word &);
        Word();
        Word(Word&);
        Word(const char *);
        ~Word();
};


#endif
