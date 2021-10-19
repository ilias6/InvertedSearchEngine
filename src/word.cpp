#include <iostream>
#include <cstring>
#include "../include/word.hpp"

using namespace std;

Word::Word(const char * s) {
    if (s != NULL) {
	this->len = strlen(s);
	this->str = new char[this->len+1];
	strncpy(this->str, s, this->len);
    }
    else {
	this->len = 0;
	this->str = NULL;
    }
}

Word::~Word() {
    if (this->str != NULL)
	delete this->str;
}

void Word::set(const char * s) {
    if (this->str != NULL)
	delete this->str;
    if (s != NULL) {
	this->len = strlen(s);
	this->str = new char[this->len+1];
	strncpy(this->str, s, this->len);
    }
    else {
	this->len = 0;
	this->str = NULL;
    }
}

void Word::print() {
    cout << str;
}
