++     	= g++
CFLAGS 	= -g -Wall -lpthread -O3 # -pg
LIBS	= -lm
TESTFLAGS= -pthread
TESTLIBS= -L ./lib/libgtest_main.a ./lib/libgtest.a

SDIR	= ./src/
ODIR 	= ./build/
IDIR 	= ./include/
BDIR	= ./bin/
TDIR	= ./test/


_OBJ 	= entry.o word.o hash_table.o hash_table_query.o query_entry.o hash_functions.o query.o BK_tree.o index.o utils.o entry_list.o core_wrapper.o core.o payload_entry.o document.o result.o scheduler.o job.o
OBJ	= $(patsubst %, $(ODIR)%, $(_OBJ))

_TESTOBJ= word_test.o test_main.o list_test.o bk_tree_test.o hash_table_test.o vector_test.o entry_test.o index_test.o entry_list_test.o query_test.o utils_test.o document_test.o result_test.o queue_test.o core_wrapper_test.o
TESTOBJ	= $(patsubst %, $(ODIR)%, $(_TESTOBJ))

_DEPS	= list.hpp entry.hpp word.hpp hash_functions.hpp hash_table.hpp document.hpp core.h query.hpp BK_tree.hpp index.hpp utils.hpp entry_list.hpp vector.hpp payload_entry.hpp queue.hpp result.hpp queue.hpp
DEPS	= $(patsubst %,	$(IDIR)%, $(_DEPS))

all:directories program all_tests
program: $(BDIR)out

all_tests:$(BDIR)tests

$(BDIR)tests: $(TESTOBJ) $(OBJ)
	$(++) -Wall -o $@ $^ $(TESTFLAGS) $(TESTLIBS)

$(BDIR)out: $(OBJ) $(ODIR)test.o
	$(++) -Wall -o $@ $^ $(CFLAGS)

$(ODIR)%.o: $(TDIR)%.cpp $(DEPS)
	$(++) -c -o $@ $< $(TESTFLAGS) -Wall

$(ODIR)scheduler.o: $(SDIR)scheduler.cpp $(IDIR)scheduler.hpp $(IDIR)core_wrapper.hpp $(IDIR)core_wrapper.hpp
	$(++) -c -o $@ $< $(CFLAGS)
$(ODIR)job.o: $(SDIR)job.cpp $(IDIR)job.hpp $(IDIR)document.hpp
	$(++) -c -o $@ $< $(CFLAGS)
$(ODIR)document.o: $(SDIR)document.cpp $(IDIR)document.hpp $(IDIR)core.h $(IDIR)word.hpp $(IDIR)hash_functions.hpp $(IDIR)hash_table.hpp
	$(++) -c -o $@ $< $(CFLAGS)
$(ODIR)payload_entry.o: $(SDIR)payload_entry.cpp $(IDIR)payload_entry.hpp $(IDIR)core.h
	$(++) -c -o $@ $< $(CFLAGS)
$(ODIR)BK_tree.o: $(SDIR)BK_tree.cpp $(IDIR)BK_tree.hpp $(IDIR)word.hpp $(IDIR)entry.hpp $(IDIR)vector.hpp
	$(++) -c -o $@ $< $(CFLAGS)
$(ODIR)entry_list.o: $(SDIR)entry_list.cpp $(IDIR)entry_list.hpp $(IDIR)hash_table.hpp $(IDIR)hash_functions.hpp $(IDIR)utils.hpp $(IDIR)word.hpp $(IDIR)entry.hpp $(IDIR)list.hpp $(IDIR)query.hpp
	$(++) -c -o $@ $< $(CFLAGS)
$(ODIR)entry.o: $(SDIR)entry.cpp $(IDIR)entry.hpp $(IDIR)list.hpp $(IDIR)word.hpp
	$(++) -c -o $@ $< $(CFLAGS)
$(ODIR)hash_functions.o: $(SDIR)hash_functions.cpp $(IDIR)hash_functions.hpp
	$(++) -c -o $@ $< $(CFLAGS)
$(ODIR)hash_table.o: $(SDIR)hash_table.cpp $(IDIR)hash_table.hpp $(IDIR)entry.hpp $(IDIR)word.hpp $(IDIR)list.hpp $(IDIR)hash_functions.hpp
	$(++) -c -o $@ $< $(CFLAGS)
$(ODIR)hash_table_query.o: $(SDIR)hash_table_query.cpp $(IDIR)hash_table_query.hpp $(IDIR)query.hpp $(IDIR)query_entry.hpp $(IDIR)list.hpp $(IDIR)hash_functions.hpp
	$(++) -c -o $@ $< $(CFLAGS)
$(ODIR)query_entry.o: $(SDIR)query_entry.cpp $(IDIR)query_entry.hpp $(IDIR)query.hpp
	$(++) -c -o $@ $< $(CFLAGS)
$(ODIR)index.o: $(SDIR)index.cpp $(IDIR)index.hpp $(IDIR)core.h $(IDIR)word.hpp $(IDIR)entry_list.hpp $(IDIR)hash_table.hpp $(IDIR)entry.hpp $(IDIR)BK_tree.hpp
	$(++) -c -o $@ $< $(CFLAGS)
$(ODIR)test.o: $(SDIR)test.cpp $(DEPS)
	$(++) -c -o $@ $< $(CFLAGS)
$(ODIR)query.o: $(SDIR)query.cpp $(IDIR)query.hpp $(IDIR)hash_table.hpp $(IDIR)hash_functions.hpp $(IDIR)utils.hpp $(IDIR)word.hpp $(IDIR)vector.hpp $(IDIR)core.h
	$(++) -c -o $@ $< $(CFLAGS)
$(ODIR)utils.o: $(SDIR)utils.cpp $(IDIR)utils.hpp $(IDIR)word.hpp $(IDIR)entry.hpp $(IDIR)core.h $(IDIR)query.hpp $(IDIR)vector.hpp
	$(++) -c -o $@ $< $(CFLAGS)
$(ODIR)core_wrapper.o: $(SDIR)core_wrapper.cpp $(IDIR)utils.hpp $(IDIR)index.hpp $(IDIR)word.hpp $(IDIR)entry.hpp $(IDIR)entry_list.hpp $(IDIR)core.h $(IDIR)query.hpp $(IDIR)vector.hpp $(IDIR)core_wrapper.hpp $(IDIR)queue.hpp $(IDIR)result.hpp $(IDIR)document.hpp $(IDIR)scheduler.hpp $(IDIR)hash_table_query.hpp
	$(++) -c -o $@ $< $(CFLAGS)
$(ODIR)word.o: $(SDIR)word.cpp $(IDIR)word.hpp
	$(++) -c -o $@ $< $(CFLAGS)
$(ODIR)core.o: $(SDIR)core.cpp $(IDIR)core.h $(IDIR)core_wrapper.hpp $(IDIR)result.hpp
	$(++) -c -o $@ $< $(CFLAGS)
$(ODIR)result.o: $(SDIR)result.cpp $(IDIR)result.hpp $(IDIR)query.hpp $(IDIR)query_entry.hpp $(IDIR)hash_table_query.hpp $(IDIR)vector.hpp $(IDIR)document.hpp $(IDIR)utils.hpp
	$(++) -c -o $@ $< $(CFLAGS)



directories:
	mkdir -p build; mkdir -p bin; mkdir -p prof;

unit-test: directories
	make all_tests; ./bin/tests

cleanO:
	rm $(ODIR)*.o

clean: cleanO
	rm $(BDIR)*
