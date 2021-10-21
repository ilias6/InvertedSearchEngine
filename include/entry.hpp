#ifndef __ENTRY_HPP__
#define __ENTRY_HPP__

#include "./word.hpp"
#include "./list.hpp"

class Entry {
    private:
	Word word;	
	List<int> payload;
    public:
	List<int> getPayload();
	void addToPayload(int);
	Word getWord() const;
	Entry(const char *, int);
	~Entry();
	bool operator==(const Entry &);
};

#endif
