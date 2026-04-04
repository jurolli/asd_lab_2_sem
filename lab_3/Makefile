build:
	gcc -c parse.c stack.c tree.c

test: build
	gcc tests.c parse.o stack.o tree.o -o tests
	./tests

all: build
	gcc main.c parse.o stack.o tree.o -o main
	./main

clean:
	rm -f *.o tests main