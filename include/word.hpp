#ifndef __WORD_HPP__
#define __WORD_HPP__


class Word {
    private:
        int len;
        char * str;
    public:
	/*Basic*/
	void set(const char *);
	int getLen();
	const char * getStr();
	void print();
	bool exactMatch(Word &);
	int hammingDist(Word &);
	int editDist(Word &);
        Word(const char *);
        ~Word();
};


#endif
