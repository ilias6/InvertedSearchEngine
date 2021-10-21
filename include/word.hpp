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
	char * getStr();
	void print();
        Word(const char *);
	bool exactMatch(const & Word);
	int hammingDist(const & Word);
	int editDist(const & Word);
        ~Word();
};


#endif
