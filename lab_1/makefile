build:
	gcc -c tree.c

main: build
	gcc -o main main.c 
	./main

test: build
	gcc -o tests tests.c
	./tests

clean:
	rm -f *.o tests main