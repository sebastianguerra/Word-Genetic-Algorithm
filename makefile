compiler=gcc
flags=-Wall -g

all: main

main: main.c
	$(compiler) $(flags) -o main main.c

.PHONY: run
run: main
	./main

.PHONY: clean
clean:
	rm -f main

.PHONY: debug
debug: main
	gdb main

.PHONY: memcheck
memcheck: main
	valgrind --leak-check=full -s ./main