# **Inverted Search Engine** *(SIGMOD 2013)*
## **sdi1700072** & **sdi1700055**

## Structure of the project:
As you can see above the project has the following directories:
 1) bin
 2) build
 3) input
 4) src
 5) include
 6) lib
 7) test

Each directory includes:
 1) the binary files
 2) the object files (.o)
 3) the input files to run the program
 4) the source files (.cpp)
 5) the header files (.hpp)
 6) the source files for unit-testing

## Structure of the project (on level of classes)

   Word   |List\<T\> |Vector\<T\>| HashTable |   Query  |   BKTree  | EntryList |  Index
--------- | -------- | --------- | --------- | -------- | --------- | --------- | --------
    _	  |     _    |     _     |  Entry *  |  Word ** |   Entry * |
    _     |     _    |     _     |     _     |     _    |Vector BKT |            | ----
