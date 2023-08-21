CFLAGS = -Wall -Wextra -Werror -Wswitch-enum -pedantic -std=gnu99 -g3 -O3 -fdiagnostics-color=always -I.
CS = main.c Token.c Lexer.c Parser.c Hashmap.c

all: main

main: $(CS)
	$(CC) $(CFLAGS) -o main $(CS)

.PHONY: run
run: main
	./main
