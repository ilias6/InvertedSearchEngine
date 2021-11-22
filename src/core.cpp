#include "../include/core.hpp"
#include "../include/core_wrapper.hpp"

unsigned int Q = 0;
CoreWrapper * CW = NULL;

ErrorCode InitializeIndex() {
    CW = new CoreWrapper(Q); 
    return EC_SUCCESS;
}
ErrorCode DestroyIndex() {
    delete CW;
    return EC_SUCCESS;
}

ErrorCode StartQuery (QueryID query_id, const char * query_str, MatchType match_type, unsigned int match_dist) {
    CW->addQuery(query_id, query_str, match_type, match_dist);
    return EC_SUCCESS;
}

ErrorCode MatchDocument(DocID doc_id, const char * doc_str) {
    return EC_SUCCESS;
}

ErrorCode GetNextAvailRes(DocID * p_doc_id, unsigned int * p_num_res, QueryID ** p_query_ids) {
    return EC_SUCCESS;
}

