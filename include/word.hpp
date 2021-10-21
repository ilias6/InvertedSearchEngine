#ifndef __WORD_HPP__
#define __WORD_HPP__


class Word {
    private:
        int len;
        char * str;
    public:
	/*Basic*/
	void set(const char *);
	int getLen() const;
	char * getStr() const;
	void print() const;
	bool exactMatch(const Word &) const;
	int hammingDist(const Word &) const;
	int editDist(const Word &) const;
        Word(const char *);
        ~Word();
};


#endif
