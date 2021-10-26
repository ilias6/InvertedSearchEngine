#include <iostream>
#include <cstring>
#include "../include/document.hpp"

using namespace std;

Document::Document(int id, char * path) {
    this->id = id;
    this->cSize = 0;
    this->wSize = 0;

    ifstream input;

    input.open(path);
    if (!input) {
	cerr << "Failed to open file: " << path << endl;
	return;
    }

    char c;
    int wordIndex = 0;
    char * buffer = new char*[32];
    while (!input.eof()) {
	input >> c;
	if (c == ' ') {
	    buffer[wordIndex] = '\0';
	    wordIndex = 0;
	    continue;
	}
	buffer[wordIndex] = c;
	wordIndex++;
    }




}
