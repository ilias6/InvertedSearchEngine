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

extern unsigned int Q;
extern CoreWrapper * CW;

int main(int argc, char * argv[]) {
    if (argc < 2){
        cerr<<"Usage: "<<argv[0]<<" [inputPath] "<<endl;
        return -1;
    }
    
    // fscanf(fp,"%[^\n]s",path);
    // printf("%s\n",path);

    // Q = 100;
    // InitializeIndex();
    // StartQuery(0, "", MT_EXACT_MATCH, 0);
    // StartQuery(1, "", MT_HAMMING_DIST, 1);
    // StartQuery(2, "", MT_EDIT_DIST, 1);
    // CW->makeIndeces();
    // DestroyIndex();
    return 0;
}
