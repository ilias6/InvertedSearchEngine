#include "../include/job.hpp"

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
