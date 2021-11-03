++     	= g++
CFLAGS 	= -g
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

_TESTOBJ= word_test.o
TESTOBJ	= $(patsubst %, $(ODIR)%, $(_TESTOBJ))

_DEPS	= list.hpp entry.hpp word.hpp hash_functions.hpp hash_table.hpp document.hpp core.hpp query.hpp BK_tree.hpp index.hpp utils.hpp entry_list.hpp
DEPS	= $(patsubst %,	$(IDIR)%, $(_DEPS))


program:$(BDIR)out
test:	$(BDIR)test

$(BDIR)test: $(OBJ) $(TESTOBJ) $(ODIR)test_main.o
	$(++) -o $@ $^ $(TESTFLAGS) $(TESTLIBS)

$(BDIR)out: $(OBJ) $(ODIR)main.o
	$(++) -o $@ $^ $(CFLAGS)

$(ODIR)%.o: $(SDIR)%.cpp $(DEPS)
	$(++) -c -o $@ $< $(CFLAGS)

$(ODIR)%.o: $(TDIR)%.cpp $(DEPS)
	$(++) -c -o $@ $< $(TESTFLAGS)


cleanO:
	rm $(ODIR)*.o

clean: cleanO
	rm $(BDIR)*
