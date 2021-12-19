# **Inverted Search Engine** *(SIGMOD 2013)*
### **sdi1700072** & **sdi1700055**

## Structure of the project:
As you can see above the project has the following directories:
 1) bin        →   the binary files
 2) build      →   the object files (.o)
 3) input      →   the input files to run the program
 4) src        →   the source files (.cpp)
 5) include    →   the header files (.hpp/.h)
 6) lib        →   the libraries that are required (only g)
 7) test       →   the source files for unit-testing

## Structure of the project (class diagram)

### Our basic classes:
Word | ListNode\<T\> | List\<T\> | Vector\<T\> | Queue\<T\> 
| :---: | :---: | :---: | :---: | :---: 
char\* string | T data | ListNode\<T\>\* head | T[Actual Size] | List\<T\> lst
int length | ListNode\<T\>* next | ListNode\<T\>\* tail | int length | _
_  | _ | int length | int actual_size | _ 

### And the composite ones:
Entry | Bucket | HashTable | Query | BKNode | BKTree | EntryList | Index | PayloadEntry | Result | CoreWrapper | Document
| :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---:
Word word | Vector\<Entry\*\> list| Bucket\* array | Word\*\* | Entry\* e | metric | List\<Entry\> list | MatchType type | QueryID id | DocID id | EntryList \* entryList | Word \*\* words
List\<PayloadEntry\> payload\[MAX_TYPES_NUM\]\[MAX_DISTANCE+1\] | _ | int size (bucket num) | QueryID id | int distance (from parent) | BKNode\* root | HashTable hashtable | BKTree\*\* trees (multiple trees for manhattan distance) | bool \* active (points to addr of Querry::active) | Vector<Query *> queries | Index \*\*\* indeces | DocID id
_ | _ | int current_size (num of Entries in all buckets) | int wordsInQuery | _ | Vector\<BKNode\*\> children | int size | _ | HashTable \* hTable | bool\*\* wordFlags | Vector\<Query \*\> \*queries | int wordsInDoc
_ | _ | hash function | MatchType type | _ | _ | _ | int numOfTrees (1 if MT_EDIT_DIST) | _ | _ | Queue<Document \*> \* docs 
_ | _ | _ | bool active | _ | _ | _ | _ | _ | _ | Queue<Result \*> \* results |
_ | _ | _ | unsigned int matchDist | _ | _ | _ | _ | _ | _ | _ |

### *A few words about our basic classes*
1. **Word**    
&emsp;We've implemented copy constructor, contsructor with char *, setters, getters and also the metric functions needed (exactMatch,editDist,hammingDist). Also we overloaded the operators \<\< (usefull for printing) and == (useful for template data comparison) that compares using exactMatch. If an empty word is to be constructed then len is 0 and str is set to NULL.  
2. **ListNode\<T\>**  
&emsp;We've implemented copy constructor, empty constructor(create empty object and set next to NULL) and getters/setters. ListNode is member of class List and contains data of type T and a pointer to the next ListNode\<T\>.  
3. **List\<T\>**  
&emsp;We've implemented needed constructors and methods for copying and appending lists. Insert has O(1) time complexity, because insert is done each time in the tail of the list. Insert method second argument is for getting the address of data contained in ListNode. Lists can be traversed by index and the caller can get node's data reference,copy and data address in memory. If index given is negative or exceeds len of list, then an invalid_argument exception is thrown indicating that index is out of range. It must be noted that remove, removes the first occurence of T object. What's more, ListErrorCode is implemented to indicate success or failure in list operations (L_SUCCESS,L_FAIL,L_EMPTY,L_NOT_EXISTS).
4. **Vector\<T\>**  
&emsp;Vector is an array containing data of type T. At the very first insert actual size of array in memory is 2 and when the third item is to be inserted, actual size of array is doubled. As for remove, when for example the previously inserted third item is removed the actual memory is cut in half. In general, when actual size in memory is to be exceeded, array is resized accordingly (doubled or cut in half) and data is copied in the newly created array (operation like realloc in c). One problem with the above is that we can have waste of memory. As with the list, if index given is negative or exceeds len (data len and not actual len) of vector, then an invalid_argument exception is thrown indicating that index is out of range. This vector was created in favor of BKTreeNode to hold its children and access them in O(1). What's more, VectorErrorCode is implemented to indicate success or failure in vector operations (V_SUCCESS,V_FAIL,V_EMPTY,V_NOT_EXISTS). UPDATE: Vector can now initialized to starting size (etc starting size 50) and works a mentioned above 

### *A few words about our composite classes*
1. **Entry**  
&emsp;Entry class contains a Word used as primary key in searches and compare operations and a List\<PayloadEntry\> payload\[MATCH_TYPES_NUM\]\[MAX_DISTANCE + 1\] (PayloadEntry contains QueryID id and the information if this query is active). MATCH_TYPES_NUM is 3 because we have 3 matching types (MT_EXACT_MATCH,MT_EDIT_DIST,MT_HAMMING_DIST) and MAX_DISTANCE is 3 (according to sigmod description). So if we want to check all MT_EXACT_MATCH queries that contain the entrie's word we would search the payload\[0\]\[0\] list (the other three are empty). If we want to find all MT_EDIT_DIST of dist 0<=j<=MAX_DISTANCE we will search payload\[1\]\[j\]. For MT_HAMMING_DIST payload\[2\]\[j\] .We've implemented needed constructors and overloaded \<\< and == operators to make our life easier. The outside world can have access to the entry's word and list, as our getters return references of the Word and the list.
2. **Bucket**  
&emsp;Bucket class is a class wrapper that actualy holds the data of hashtable and contains a List\<Entry *\> for handling collisions in our static hashtable. Bucket's methods just call list's operations. It must be noted that list hols Entry *, because we don't want to create the same objects over and over again. Entry pointers point to the EntryList list data which are of type Entry.
3. **HashTable**  
&emsp;Hashtable contains a Bucket array and its size (preferably use a prime number) and a pointer to a hash function (hash functions exist in hash_functions.cpp) + a size (current_size) that indicates number of Entries in all Buckets. Inserting and removing from hashtable is done with the usual method. **If number of all records is bigger than 2*0.9*size then the bucket array is doubled and all keys are rehashed!**.What's more, HashTableErrorCode is implemented to indicate success or failure in HashTable operations (H_T_SUCCESS,H_T_FAIL).  
4.**Query**  
&emsp;Query class holds an array of Word *,its' size, the querie's id, the MatchType, a bool indicating if active and an unsigned int matchDist.Query constructor makes sure that no duplicates are stored in the array (uses a local hashtable constructed inside for that purpose).
5. **EntryList**  
&emsp;EntryList contains a HashTable and a List\<Entry\>. Public method insert takes a Query as argument and calls private method insert with Word * and int (queryId). Private insert first check existance of word. If word doesn't exist, then insert it in the list (O(1)) and get the address of Entry (in ListNode) and then insert tha address (Entry *) in the hashtable O(1). If word already exists then HashTable::updateEntryPayload updates list of queryIds that word exist. Query class will make sure that no same words are read from a query (duplicate words in query may and preferably not exist), so payload list won't contain a queryId more than once. It should be noted that when we update an Entry * in hashtable, it is also updated in the list (O(1)). HashTable helps as so as not to search the whole list to update an entry's payload in O(n). What's more, HashTableErrorCode is implemented to indicate success or failure in EntryList operations (E_L_SUCCESS,E_L_FAIL).  
6. **BKNode**\
&emsp;Contains a pointer to an Entry (initially inserted in an EntryList), an integer that represents the distance (by the defined metric)
and a Vector of pointers to BKNodes that represent the children of this BKNode.
7. **BKTree**\
&emsp;During the construction of this class, the metric function is defined and the root pointer is initially set to NULL. The insert method takes the Entry *
parameter and to achieve the recursive insertion in the tree, calls a private insert method on the root BKNode pointer. The search method similarly and returns 
the results in a List of Entry pointers.
8. **Index**\
&emsp;For a given Matchtype-Match Distance an Index is built. The entries are inserted dynammically. When we search for a word in our index, the MatchType is checked and the corresponding lookup is made.\
9. **Result**\
&emsp;Contains the matched queries for a document. The queries are updated dynammically via a bool array that expresses if a word is matched.
With the fetch method the bool array is parsed and the proper querries are returned.\
10. **Document**\
&emsp;Document class holds an array of Word *,its' size, the document's id. Document constructor makes sure that no duplicates are stored in the array (uses a local hashtable constructed inside for that purpose).
11. **CoreWrapper**\
&emsp;This class is used as a global struct that contains all the data-structs of the program. Sigmod's core methods are implemented in this one.
The Index* 2-d array is used to devide the data in an efficient way. Index[0][0] corresponds to exact-match entries. One the other hand, Index[1] and Index[2]
contain entries that require edit/hamming distance match. Then, Index[i][j] corresponds to i-type and j-distance.
The search-match is made with the following algorimth:
```
For each Word in Document:
  For each MatchType:
    For each Distance: (exact match is defined with distance=0)
      update the Result struct
```

**For all templates, it is important to say that if the data type is pointer, it's programmer's responsibility to free the memory!** 

***Gtest was used for unit testing.***
We used the gtest framework for unit-testing. The two .a files in lib/ are linked at the compilation of the unit-test binary. The gtesh.h header file
is located in the include directory.  
##Run tests:
```bash
make unit-test
```
## Make it run!
### For the main program, run the Makefile first:
```bash
make clean; make && ./bin/out ./input/small_test.txt
```
### Shared library
To generate the shared library do:
```bash
make
```
### Profiling
In the Makefile the -pg flag is commented out. Use if you want to run the gprof profiler with:
```bash
make clean ; make && ./bin/out ./input/small_text.txt && gprof ./bin/out ./gmon.out > <YOUR FILE>
