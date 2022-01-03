#include <cstdlib>

enum JobErrorCode{J_SUCCESS, J_FAIL};
enum JobId{Search, ExactSearch, EditSearch, HammingSearch};

class Job {
    private:
        JobId id;        
    public:
        Job(JobId);
        ~Job();
};
