#include "../include/core.hpp"
#include "../include/core_wrapper.hpp"
#include "../include/result.hpp"


CoreWrapper * CW = NULL;


ErrorCode InitializeIndex() {
    CW = new CoreWrapper();
    return EC_SUCCESS;
}
ErrorCode DestroyIndex() {
    delete CW;
    return EC_SUCCESS;
}

ErrorCode StartQuery (QueryID query_id, const char * query_str, MatchType match_type, unsigned int match_dist) {
    CoreWrapperErrorCode c_err;
    c_err=CW->addQuery(query_id, query_str, match_type, match_dist);

    return EC_SUCCESS;
}

ErrorCode EndQuery (QueryID query_id) {
    CW->deactivateQuery(query_id);
    return EC_SUCCESS;
}

ErrorCode MatchDocument(DocID doc_id, const char * doc_str) {

    //master thread construct doc and add to pool

    //threads read from pool and do the search and fill results

    return EC_SUCCESS;
}

ErrorCode GetNextAvailRes(DocID * p_doc_id, unsigned int * p_num_res, QueryID ** p_query_ids) {
    // master thread collect results
    return EC_SUCCESS;
}
