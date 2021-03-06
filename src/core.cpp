#include "../include/core.h"
#include "../include/core_wrapper.hpp"
#include "../include/result.hpp"
#include <unistd.h>

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
    if(c_err==C_W_FAIL)
        return EC_FAIL;
    return EC_SUCCESS;
}

ErrorCode EndQuery (QueryID query_id) {
    if(CW->deactivateQuery(query_id)==C_W_SUCCESS)
        return EC_SUCCESS;
    // return EC_FAIL;
    return EC_SUCCESS;

}

ErrorCode MatchDocument(DocID doc_id, const char * doc_str) {

    //master thread construct doc and add to pool
    Document * doc=new Document(doc_id, doc_str);
    if (CW->matchDocument(doc) != C_W_SUCCESS)
        return EC_FAIL;
    // delete doc_to_be_matched;
    return EC_SUCCESS;
}

ErrorCode GetNextAvailRes(DocID * p_doc_id, unsigned int * p_num_res, QueryID ** p_query_ids) {
    // master thread collect results
    Result * res=CW->pullResult();
    if(res==NULL){
        cerr<<"PULLED NULL RESULT!"<<endl;
        return EC_FAIL;
    }
    ResultErrorCode err=res->fetch(p_doc_id,p_num_res,p_query_ids);
    if(err!=R_SUCCESS){
        cerr<<"RESULT FETCH FAILED!"<<endl;
        return EC_FAIL;
    }
    delete res;
    return EC_SUCCESS;
}
