CFLAGS = -Wall -Wextra -pedantic -std=c99 -g3 -O3
CS = main.c Token.c Lexer.c

all: main

main: $(CS)
	cc $(CFLAGS) -o main $(CS)

.PHONY: run
run: main
	./main
