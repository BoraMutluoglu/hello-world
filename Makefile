cxx = gcc -std=c99

cflags = -O3 -g -Wall --pedantic -fopenmp -funroll-loops -DNDEBUG


rootPath = ./
libPath = ${rootPath}impl/
headers = ${rootPath}inc/
binPath = ${rootPath}bin/

libSources = ${libPath}*.c


all: dictionary.a
	${cxx} ${cflags} -I inc -I ${headers} -o ${binPath}test_dictionary ${rootPath}test_dictionary.c ${binPath}dictionary.a
	chmod ugo+xwr ${binPath}test_dictionary

dictionary.a :
	mkdir -v -p ${binPath}
	${cxx} ${cflags} -I ${headers} -c ${libSources}
	ar rc dictionary.a *.o
	ranlib dictionary.a
	rm *.o
	mv dictionary.a ${binPath}

.PHONY: all dictionary.a
