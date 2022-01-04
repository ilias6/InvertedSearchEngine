#include "../include/job.hpp"
#include <iostream>

using namespace std;
Job::Job(JobId id, SearchArgs * searchArgs) {
    this->id = id;
    this->searchArgs = searchArgs;
}

Job::~Job() {
    if (this->id == SEARCH)
        delete this->searchArgs;
}

SearchArgs::SearchArgs(Document * doc) {
    this->doc = doc;
}

SearchArgs::~SearchArgs() {}

Document * SearchArgs::getDocument() {
    return this->doc;
}

void SearchArgs::print(){
    cout<<"\tdoc_id: "<<this->doc->getId()<<endl;
    // this->doc->print();
}

void Job::print(){
    cout<<"\tTASK: ";
    switch(id){
        case SEARCH:
            cout<<"SEARCH "<<endl;
            break;
        case EXACTSEARCH:
            cout<<"EXACTSEARCH "<<endl;
            break;
        case EDITSEARCH:
            cout<<"EDITSEARCH "<<endl;
            break;
        case HAMMINGSEARCH:
            cout<<"HAMMINGSEARCH "<<endl;
            break;
        default:
            cout<<" - "<<endl;
            break;
    }
    searchArgs->print();
}
