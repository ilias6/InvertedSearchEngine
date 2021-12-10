#include <iostream>
#include <cstring>
#include "../include/word.hpp"

using namespace std;

Word::Word(const char * s) {
    if (s != NULL && strlen(s) != 0) {
        this->len = strlen(s);
        this->str = new char[this->len+1];
        strncpy(this->str, s, this->len);
        this->str[this->len] = '\0';
    }
    else {
        this->len = 0;
        this->str = NULL;
    }
}
Word::Word() {
    this->len=0;
    this->str=NULL;
}

Word::Word(Word &w) {
    const char * s = w.getStr();
    if (s == NULL || strlen(s) == 0) {
        this->len = 0;
        this->str = NULL;
        return;
    }
    this->len = strlen(s);
    this->str = new char[this->len+1];
    strncpy(this->str, s, this->len);
    this->str[this->len] = '\0';
}

Word::~Word() {
    if (this->str != NULL){
        //cout << "Deleting " << this->str << endl;
        delete[] this->str;
    }
}

void Word::set(const char * s) {
    if (this->str != NULL)
           delete[] this->str;

    if (s != NULL && strlen(s) != 0) {
        this->len = strlen(s);
        this->str = new char[this->len+1];
        strncpy(this->str, s, this->len);
        this->str[this->len] = '\0';
    }
    else {
       this->len = 0;
       this->str = NULL;
    }
}

ostream & operator<<(ostream & os, const Word & e) {
    os << e.str;
    return os;
}

int Word::getLen() {
    return this->len;
}

const char * Word::getStr() {
    return this->str;
}

bool Word::operator==(Word & w) {
    return this->exactMatch(w);
}

bool Word::exactMatch(Word & w) {
    if (this->len != w.len)
        return false;

    const char * str = w.getStr();
    for (int i = 0; i < this->len; ++i)
        if (this->str[i] != str[i])
            return false;
    return true;
}

int Word::hammingDist(Word &w) {
    if (this->len != w.len)
        return -1;

    int counter = 0;
    for (int i = 0; i < this->len; ++i)
        if (this->str[i] != w.str[i])
            ++counter;
    return counter;
}

int Word::editDist(Word &w) {
    int l1 = this->len;
    int l2 = w.len;

    if (l1 == 0)
        return l2;
    if (l2 == 0)
        return l1;

    char * str1 = this->str;
    char * str2 = w.str;
    int ** v = new int*[l1+1];
    for (int i = 0; i < l1+1; ++i)
        v[i] = new int[l2+1];

    for (int i = 0; i < l1+1; i++) {
        v[i][0] = i;
    }
    for (int j = 0; j < l2+1; j++) {
        v[0][j] = j;
    }

    for (int i = 0; i < this->len; ++i) {
        for (int j = 0; j < w.len; ++j) {
            if (str1[i] == str2[j])
                v[i+1][j+1] = v[i][j];
            else
                v[i+1][j+1] = 1 + min(min(v[i+1][j], v[i][j+1]), v[i][j]);
        }

    }

    int diff = v[l1][l2];
    for (int i = 0; i < l1+1; ++i)
        delete[] v[i];
    delete[] v;

    return diff;
}
