#include <iostream>
#include <cstdlib>
#include "../include/list.hpp"
#include "../include/entry.hpp"
#include "../include/word.hpp"
#include "../include/hash_table.hpp"
#include "../include/hash_functions.hpp"
#include "../include/document.hpp"
#include "../include/core.hpp"
#include "../include/query.hpp"
#include "../include/BK_tree.hpp"
#include "../include/index.hpp"
#include "../include/utils.hpp"
#include "../include/entry_list.hpp"
#include "../include/core_wrapper.hpp"
#include <unistd.h>
#include <cstring>
#include <fstream>



using namespace std;

char temp[MAX_DOC_LENGTH];

void TestSigmod(const char* test_file_str)
{
    int i, j;
    printf("Start Test ...\n"); fflush(NULL);
    FILE* test_file=fopen(test_file_str, "rt");

    if(!test_file) {
        printf("Cannot Open File %s\n", test_file_str);
        fflush(NULL);
        return;
    }

    InitializeIndex();

    unsigned int first_result=0;
    int num_cur_results=0;

    const int max_results=100;

    bool cur_results_ret[max_results];
    unsigned int cur_results_size[max_results];
    unsigned int* cur_results[max_results];

    while(1) {
        char ch;
        unsigned int id;

        if(EOF==fscanf(test_file, "%c %u ", &ch, &id))
            break;


        if(ch=='s') {
            int match_type;
            int match_dist;

            if(EOF==fscanf(test_file, "%d %d %*d %[^\n\r] ", &match_type, &match_dist, temp)) {
                printf("Corrupted Test File.\n");
                fflush(NULL);
                return;
            }

            ErrorCode err=StartQuery(id, temp, (MatchType)match_type, match_dist);

            if(err==EC_FAIL) {
                printf("The call to StartQuery() returned EC_FAIL.\n");
                fflush(NULL);
                return;
            }
            else if(err!=EC_SUCCESS) {
                printf("The call to StartQuery() returned unknown error code.\n");
                fflush(NULL);
                return;
            }
        }
        else if(ch=='e') {
            ErrorCode err=EndQuery(id);

            if(err==EC_FAIL) {
                printf("The call to EndQuery() returned EC_FAIL.\n");
                fflush(NULL);
                return;
            }
            else if(err!=EC_SUCCESS) {
                printf("The call to EndQuery() returned unknown error code.\n");
                fflush(NULL);
                return;
            }
        }
        else if(ch=='m') {
            if(EOF==fscanf(test_file, "%*u %[^\n\r] ", temp)) {
                printf("Corrupted Test File.\n");
                fflush(NULL);
                return;
            }

            //ErrorCode err=MatchDocument(id, temp);

            if(err==EC_FAIL) {
                printf("The call to MatchDocument() returned EC_FAIL.\n");
                fflush(NULL);
                return;
            }
            else if(err!=EC_SUCCESS) {
                printf("The call to MatchDocument() returned unknown error code.\n");
                fflush(NULL);
                return;
            }
        }
        else if(ch=='r') {
            unsigned int num_res=0;
            if(EOF==fscanf(test_file, "%u ", &num_res)) {
                printf("Corrupted Test File.\n");
                fflush(NULL);
                return;
            }

            unsigned int qid;

            for(i=0;i<(int)num_res;i++) {
                if(EOF==fscanf(test_file, "%u ", &qid)) {
                    printf("Corrupted Test File.\n");
                    fflush(NULL);
                    return;
                }

            }
        }
        else {
            printf("Corrupted Test File. Unknown Command %c.\n", ch);
            fflush(NULL);
            return;
        }
    }

    DestroyIndex();
    fclose(test_file);
}

///////////////////////////////////////////////////////////////////////////////////////////////

int main(int argc, char* argv[]) {
    if(argc<=1)
        TestSigmod("./test_data/small_test.txt");
    else
        TestSigmod(argv[1]);
    return 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////

