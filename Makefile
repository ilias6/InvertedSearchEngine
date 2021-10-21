++     	= g++
CFLAGS 	= -g
LIBS	= -lm


SDIR	= ./src/
ODIR 	= ./build/
IDIR 	= ./include/
BDIR	= ./bin/


_OBJ 	= list.o entry.o word.o main.o
OBJ	= $(patsubst %, $(ODIR)%, $(_OBJ))

_DEPS	= list.hpp entry.hpp word.hpp
DEPS	= $(patsubst %,	$(IDIR)%, $(_DEPS))


$(BDIR)out: $(OBJ)
	$(++) -o $@ $^ $(CFLAGS)

$(ODIR)%.o: $(SDIR)%.cpp $(DEPS)
	$(++) -c -o $@ $< $(CFLAGS)


cleanO: 
	rm $(ODIR)*.o 

cleanAll: cleanO
	rm $(BDIR)*
