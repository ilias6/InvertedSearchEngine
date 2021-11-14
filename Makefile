++     	= g++
CFLAGS 	= #-g
LIBS	= -lm
TESTFLAGS= -pthread
TESTLIBS= -L ./lib/libgtest_main.a ./lib/libgtest.a


SDIR	= ./src/
ODIR 	= ./build/
IDIR 	= ./include/
BDIR	= ./bin/
TDIR	= ./test/


_OBJ 	= list.o entry.o word.o hash_table.o hash_functions.o document.o query.o BK_tree.o index.o utils.o entry_list.o
OBJ	= $(patsubst %, $(ODIR)%, $(_OBJ))

_TESTOBJ= word_test.o test_main.o list_test.o bk_tree_test.o hash_table_test.o vector_test.o entry_test.o #index_test.o entry_list_test.o
TESTOBJ	= $(patsubst %, $(ODIR)%, $(_TESTOBJ))

_DEPS	= list.hpp entry.hpp word.hpp hash_functions.hpp hash_table.hpp document.hpp core.hpp query.hpp BK_tree.hpp index.hpp utils.hpp entry_list.hpp vector.hpp
DEPS	= $(patsubst %,	$(IDIR)%, $(_DEPS))


all: apt directories program all_tests
program: $(BDIR)out
all_tests:$(BDIR)tests

$(BDIR)tests: $(TESTOBJ) $(OBJ)
	$(++) -Wall -o $@ $^ $(TESTFLAGS) $(TESTLIBS)

$(BDIR)out: $(OBJ) $(ODIR)main.o
	$(++) -Wall -o $@ $^ $(CFLAGS)

$(ODIR)%.o: $(TDIR)%.cpp $(DEPS)
	$(++) -c -o $@ $< $(TESTFLAGS)

$(ODIR)%.o: $(SDIR)%.cpp $(DEPS)
	$(++) -c -o $@ $< $(CFLAGS)


directories:
	mkdir -p build; mkdir -p bin

apt:
	sudo apt-get install libgtest-dev

cleanO:
	rm $(ODIR)*.o

clean: cleanO
	rm $(BDIR)*
