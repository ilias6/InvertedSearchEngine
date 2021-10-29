#include <iostream>
#include <cstring>
#include "../include/document.hpp"
#include "../include/core.hpp"
#include "../include/hash_table.hpp"
#include "../include/hash_functions.hpp"
#include <fstream>
#include <cstring>
#include <cerrno>

using namespace std;
bool charInWhitespaces(char c){
    if(c=='\n'||c=='\t'||c==' '||c=='\f'||c=='\r')
        return true;
    return false;
}
Document::Document(int id, const char * path) {
    this->id = id;
    this->wordsInDoc=0 ;
    this->docPath=new char[strlen(path)+1];
    this->word=new Word*[MAX_DOC_WORDS];
    if(this->word==NULL || this->docPath==NULL){
        cerr << "Failed to allocate memmory to fetch doc words!"<<endl;
        return;
    }
    strcpy(docPath,path);
    // this is for finding duplicates in 0(1)
    HashTable hashtable(3,djb2);
    // MAYBE CHECK IF FILE IS SMALLER THAN MAX_DOC_LENGTH AND OPEN OR THROW ERROR MESSAGE
    ifstream input(docPath);

    if (!input.is_open()) {
	       cerr << "Failed to open file."<<strerror(errno)<<":" << path << endl;
	       return;
    }

    int buffIndex;
    char * buffer = new char[MAX_WORD_LENGTH+1];
    while (!input.eof()) {
        buffIndex=0;
        input.get(buffer[buffIndex]);
        while(!charInWhitespaces(buffer[buffIndex]) && !input.eof()){
            //we dont want new lines
            buffIndex++;
            input.get(buffer[buffIndex]);
            if(buffIndex==MAX_WORD_LENGTH){
                cout<<buffer<<endl;
                cerr << "Document contains words with len exceeding MAX_WORD_LENGTH (" << MAX_WORD_LENGTH <<")"<< endl;
     	        return;
            }

        }
        if(buffIndex==0)
            continue;
        // we dont want space char or any whitspace
        buffIndex--;
        if(buffIndex<MIN_WORD_LENGTH-1){
            cerr << "Document contains words with len smaller than MIN_WORD_LENGTH (" << MIN_WORD_LENGTH <<")"<< endl;
            return;
        }
        buffer[buffIndex+1]='\0';//terminate string
        Word * w=new Word(buffer);
        Entry * e=hashtable.getEntry(w);
        if(e!=NULL){
            // means word already exists
            // cout<<*w<<" already exists!"<<endl;
            delete w;
            continue;
        }
        //word doen't exist so add it to array and to hashtable
        this->word[this->wordsInDoc]=w;
        e=new Entry(*w,this->id);
        hashtable.insert(e);
        this->wordsInDoc++;
        if(this->wordsInDoc==MAX_DOC_WORDS){
            cerr << "Document contains more words than MAX_DOC_WORDS (" << MAX_DOC_WORDS <<")"<< endl;
            return;
        }
    }
    // now that we know the size of word array
    // make a smaller array containing the exact number of words
    Word **tmp=this->word;
    this->word=new Word*[wordsInDoc];
    if(this->word==NULL){
        cerr << "Failed to allocate memmory to fetch doc words!"<<endl;
        return;
    }
    for(int i=0;i<wordsInDoc;i++)
    this->word[i]=tmp[i];
    delete[] tmp;
    delete[] buffer;
    hashtable.deleteData();
}
Document::~Document(){
    delete[] docPath;
    for(int i=0;i<wordsInDoc;i++)
        delete this->word[i];
    delete[] this->word;
}
int Document::getId(){
    return this->id;
}
int Document::getWordsInDoc(){
    return wordsInDoc;
}

Word *Document::getWord(int indx){
    if(indx<this->wordsInDoc){
        return word[indx];
    }
    return NULL;
}


void Document::print(){
    cout<<"------------------------"<<endl;
    cout<<"DocPath: "<<docPath<<endl;
    cout<<"Id: "<<this->id<<endl;
    cout<<"WordsInDoc: "<<wordsInDoc<<endl;
    for(int i=0;i<wordsInDoc;i++)
        cout<<"\t"<<*word[i]<<" "<<word[i]->getLen()<<endl;

    return ;
}
