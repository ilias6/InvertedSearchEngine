# **Inverted Search Engine** *(SIGMOD 2013)*
### **sdi1700072** & **sdi1700055**

## Structure of the project:
As you can see above the project has the following directories:
 1) bin        →   the binary files
 2) build      →   the object files (.o)
 3) input      →   the input files to run the program
 4) src        →   the source files (.cpp)
 5) include    →   the header files (.hpp/.h)
 6) lib        →   the libraries that are required (only gtest)
 7) test       →   the source files for unit-testing

## Structure of the project (class diagram)

### Our basic classes:
Word | ListNode\<T\> | List\<T\> | Vector\<T\>
| :---: | :---: | :---: | :---:
char\* string | T data | ListNode\<T\>\* head | T[Actual Size]
int length | ListNode\<T\>* next | ListNode\<T\>\* tail | int length
_  | _ | int length | int actual_size |

### And the composite ones:
Entry | Bucket | HashTable | Query | BKNode | BKTree | EntryList | Index
| :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---:
Word w | List\<Entry\*\> | Bucket\* array | Word\*\* | Entry\* e | metric | List\<Entry\> list | MatchType
List\<int\> payload | _ | int size | int id | int distance (from parent) | BKNode\* root | HashTable t | BKTree\*\* trees (multiple trees for manhattan distance)
_ | _ | hash function | int numOfWords | Vector\<BKTreeNode\*\> children | int size | _ | HashTable \*

### *A few words about our basic classes*
1. **Word**    
&emsp;We've implemented copy constructor, contsructor with char *, setters, getters and also the metric functions needed (exactMatch,editDist,hammingDist). Also we overloaded the operators \<\< (usefull for printing) and == (useful for template data comparison) that compares using exactMatch. If an empty word is to be constructed then len is 0 and str is set to NULL.  
2. **ListNode\<T\>**  
&emsp;We've implemented copy constructor, empty constructor(create empty object and set next to NULL) and getters/setters. ListNode is member of class List and contains data of type T and a pointer to the next ListNode\<T\>.  
3. **List\<T\>**  
&emsp;We've implemented needed constructors and methods for copying and appending lists. Insert has O(1) time complexity, because insert is done each time in the tail of the list. Insert method second argument is for getting the address of data contained in ListNode. Lists can be traversed by index and the caller can get node's data reference,copy and data address in memory. If index given is negative or exceeds len of list, then an invalid_argument exception is thrown indicating that index is out of range. It must be noted that remove, removes the first occurence of T object. What's more, ListErrorCode is implemented to indicate success or failure in list operations (L_SUCCESS,L_FAIL,L_EMPTY,L_NOT_EXISTS).
4. **Vector\<T\>**  
&emsp;Vector is an array containing data of type T. At the very first insert actual size of array in memory is 2 and when the third item is to be inserted, actual size of array is doubled. As for remove, when for example the previously inserted third item is removed the actual memory is cut in half. In general, when actual size in memory is to be exceeded, array is resized accordingly (doubled or cut in half) and data is copied in the newly created array (operation like realloc in c). One problem with the above is that we can have waste of memory. As with the list, if index given is negative or exceeds len (data len and not actual len) of vector, then an invalid_argument exception is thrown indicating that index is out of range. This vector was created in favor of BKTreeNode to hold its children and access them in O(1). In the next part we consider adding a resize method so as not to waste resources. What's more, VectorErrorCode is implemented to indicate success or failure in vector operations (V_SUCCESS,V_FAIL,V_EMPTY,V_NOT_EXISTS).

### *A few words about our composite classes*
1. **Entry**  
&emsp;Entry class contains a Word used as primary key in searches and compare operations and a List\<int\> that contains the query ids where this word exist. We've implemented needed constructors and overloaded \<\< and == operators to make our life easier. The outside world can have access to the entry's word and list, as our getters return references of the Word and the list.
2. **Bucket**  
&emsp;Bucket class is a class wrapper that actualy holds the data of hashtable and contains a List\<Entry *\> for handling collisions in our static hashtable. Bucket's methods just call list's operations. It must be noted that list hols Entry *, because we don't want to create the same objects over and over again. Entry pointers point to the EntryList list data which are of type Entry.
3. **HashTable**  
&emsp;Hashtable contains a Bucket array and its size (preferably use a prime number) and a pointer to a hash function (hash functions exist in hash_functions.cpp). Inserting and removing from hashtable is done with the usual method. What's more, HashTableErrorCode is implemented to indicate success or failure in HashTable operations (H_T_SUCCESS,H_T_FAIL).  
4.**Query**  
&emsp;Query class constructor opens a file (provided as char * path) which will be treated as a single query (1 file==1 query). Query class holds an array of Word *,its' size, the queries' id and the path to particular file. At first we don't know the actual size of words contained in file. So the word array size is set to MAX_QUERY_WORDS and later is resized to the actual wordsInQuery size. Query constructor makes sure that no duplicates are stored in the array (uses a local hashtable constructed inside for that purpose).
5. **EntryList**  
&emsp;EntryList contains a HashTable and a List\<Entry\>. Public method insert takes a Query as argument and calls private method insert with Word * and int (queryId). Private insert first check existance of word. If word doesn't exist, then insert it in the list (O(1)) and get the address of Entry (in ListNode) and then insert tha address (Entry *) in the hashtable O(1). If word already exists then HashTable::updateEntryPayload updates list of queryIds that word exist. Query class will make sure that no same words are read from a query (duplicate words in query may and preferably not exist), so payload list won't contain a queryId more than once. It should be noted that when we update an Entry * in hashtable, it is also updated in the list (O(1)). HashTable helps as so as not to search the whole list to update an entry's payload in O(n). What's more, HashTableErrorCode is implemented to indicate success or failure in EntryList operations (E_L_SUCCESS,E_L_FAIL).  
6. **BKNode**
&emsp;Contains a pointer to an Entry (initially inserted in an EntryList), an integer that represents the distance (by the defined metric)
and a Vector of pointers to BKNodes that represent the children of this BKNode.
7. **BKTree**
&emsp;During the construction of this class, the metric function is defined and the root pointer is initially set to NULL. The insert method takes the Entry *
parameter and to achieve the recursive insertion in the tree, calls a private insert method on the root BKNode pointer. The search method similarly and returns 
the results in a List of Entry pointers.
8. **Index**
&emsp;For a given EntryList and a MatchType, an Index is built. When we search for a word in our index, the MatchType is checked and the corresponding lookup
is being done.

**For all templates, it is important to say that if the data type is pointer, it's programmer's responsibility to free the memory!** 

***Gtest was used for unit testing.***
We used the gtest framework for unit-testing. The two .a files in lib/ are linked at the compilation of the unit-test binary. The gtesh.h header file
is located in the include directory.
\

## Make it run!
For this first part of the project, the input to test our program has the following struct: one file represents one query. The query file
has five words at maximum (whatever whitespaces are skipped).\
So a bash script is written, that for a given file of words, produces files with <6 words.\
The script (make_query_files.sh) is located in the input directory. Also, a file that contains a lot of words is provided for this purpose.
### Execution example:
```bash
./input/make_query_files.sh ./input/words 10000
```
The second parameter stands for the number of files to be made.

### For the main program, run the Makefile first:
```bash
make
```
As we said before, the bin/ directory contains the "out" and the "test" binary files.\
Execution examples for the first one:
```bash
./bin/out ./queries/ 5000
```
The queries directory is made by the script, so check where it is created before running this one.

```bash
./bin/out ./input/queries/ 10000
```
Execution example for the second one:
```bash
./bin/test
```
