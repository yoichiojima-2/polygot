main: main.c test.c
	gcc main.c test.c -o main

test: main
	./main test

format:
	clang-format -i *.c
