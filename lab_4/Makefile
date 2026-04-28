build:
	gcc -c tree.c

all: build
	gcc main.c tree.o -o main
	./main

run_file: build
	gcc main.c tree.o -o main
	./main input.txt

test: build
	
	gcc tests.c tree.o -o tests
	./tests

clean:
	rm -f *.o main tests