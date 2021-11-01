++     	= g++
CFLAGS 	= -g
LIBS	= -lm


SDIR	= ./src/
ODIR 	= ./build/
IDIR 	= ./include/
BDIR	= ./bin/


_OBJ 	= list.o entry.o word.o main.o hash_table.o hash_functions.o document.o query.o BK_tree.o index.o utils.o
OBJ	= $(patsubst %, $(ODIR)%, $(_OBJ))

_DEPS	= list.hpp entry.hpp word.hpp hash_functions.hpp hash_table.hpp document.hpp core.hpp query.hpp BK_tree.hpp index.hpp utils.hpp
DEPS	= $(patsubst %,	$(IDIR)%, $(_DEPS))


$(BDIR)out: $(OBJ)
	$(++) -o $@ $^ $(CFLAGS)

$(ODIR)%.o: $(SDIR)%.cpp $(DEPS)
	$(++) -c -o $@ $< $(CFLAGS)


cleanO:
	rm $(ODIR)*.o

cleanAll: cleanO
	rm $(BDIR)*
