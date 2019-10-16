CC=g++
CXXFLAGS += -march=native -frename-registers -funroll-loops -Ofast -ansi -DNDEBUG -Wall $(PROF_GEN_USE)

default:
	rm -f *.o jabi
	make PROF_GEN_USE=-fprofile-use jabi
   
profgen:
	make PROF_GEN_USE=-fprofile-generate jabi
	./jabi tiny.b

install: jabi
	cp jabi /usr/bin

clean:
	rm jabi
	rm jabi.gcda
