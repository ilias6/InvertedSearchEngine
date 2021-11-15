# **Inverted Search Engine** *(SIGMOD 2013)*
### **sdi1700072** & **sdi1700055**

## Structure of the project:
As you can see above the project has the following directories:
 1) bin        →   the binary files
 2) build      →   the object files (.o)
 3) input      →   the input files to run the program
 4) src        →   the source files (.cpp)
 5) include    →   the header files (.hpp)
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
3. **ListNode\<T\>**  
&emsp;We've implemented copy constructor, empty constructor(create empty object and set next to NULL) and getters/setters. ListNode is member of class List and contains data of type T and a pointer to the next ListNode\<T\>.  
5. **List\<T\>**
&emsp;We've implemented needed constructors and methods for copying and appending lists. Insert has O(1) time complexity, because insert is done each time in the tail of the list. Lists can be traversed by index and the caller can get node's data reference,copy and data address in memory. If index given is negative or exceeds len of list, then an invalid_argument exception is thrown indicating that index is out of range. It must be noted that remove, removes the first occurence of T object. What's more, ListErrorCode is implemented to indicate success or failure in list operations (L_SUCCESS,L_FAIL,L_EMPTY,L_NOT_EXISTS).
7. **Vector\<T\>**  
&emsp;Vector is an array containing data of type T. At the very first insert actual size of array in memory is 2 and when the third item is to be inserted, actual size of array is doubled. As for remove, when for example the previously inserted third item is removed the actual memory is cut in half. In general, when actual size in memory is to be exceeded, array is resized accordingly (doubled or cut in half) and data is copied in the newly created array (operation like realloc in c). One problem with the above is that we can have waste of memory. This vector was created in favor of BKTreeNode to hold its children and access them in O(1). In the next part we consider adding a resize method so as not to waste resources.

### *A few words about our composite classes*
1. **Entry**
2. **Bucket**
3. **HashTable**
4. **EntryList**
5. **BKNode**
6. **BKTree**
7. **Index**
8. **Query**

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
In the Makefile, the command:
```bash
sudo apt-get install libgtest-dev
```
is needed, as we used the gtest framework for unit-testing. The two .a files in lib/ are linked at the compilation of the unit-test binary, so that is the only thing that you must install to your system.\
\
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
