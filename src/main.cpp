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


using namespace std;

int main(int argc, char * argv[]) {

    time_t cur;
    cur=time(NULL);
    Query q2(1,"input/words3");
    cur=time(NULL)-cur;
    float elapsed=(float)cur/60;
    cout<<"Query build time: "<<elapsed<<endl;;
    EntryList lst;
    cur=time(NULL);
    lst.insert(q2);
    cur=time(NULL)-cur;
    elapsed=(float)cur/60;
    cout<<"Insert time: "<<elapsed<<endl;;
    cur=time(NULL);
    Index indx(lst,MT_HAMMING_DIST);
    cur=time(NULL)-cur;
    elapsed=(float)cur/60;
    cout<<"Index build time: "<<elapsed<<endl;
    Word w("abak");
    cur=time(NULL);
    List<Entry*> res=indx.search(&w,1);
    cur=time(NULL)-cur;
    elapsed=(float)cur/60;
    cout<<"Search time: "<<elapsed<<endl;
    for (int i = 0; i < res.getLen(); ++i)
        cout << res.getItem(i)->getWord() << endl;
    return 0;

}
