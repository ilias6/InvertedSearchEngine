#ifndef __WORD_HPP__
#define __WORD_HPP__


class Word {
    private:
        int len;
        char * str;
    public:
	/*Basic*/
	void set(const char *);
	void print();
        Word(const char *);
	/*cmp(const char *);*/
        ~Word();
};


#endif
