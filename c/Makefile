CC = gcc
CFLAGS = -Wall -Wextra -g

all: main test

main: main.c functions.c
	$(CC) $(CFLAGS) -o main main.c functions.c

test: test_main.c functions.c
	$(CC) $(CFLAGS) -o test test_main.c functions.c

clean:
	rm -f main test *.o

.PHONY: all clean