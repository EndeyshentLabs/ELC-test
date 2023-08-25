CFLAGS = -Wall -Wextra -Werror -Wswitch-enum -pedantic -std=gnu99 -g3 -O3 -fdiagnostics-color=always -I.
CS = Token.c Lexer.c Parser.c Hashmap.c
OBJS = $(CS:.c=.o)

all: libelc.a

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

libelc.a: $(OBJS)
	ar -crs libelc.a $(OBJS)

main: main.c libelc.a
	$(CC) $(CFLAGS)-o main main.c -L. -lelc

.PHONY: run
run: main
	./main

.PHONY: clean
clean:
	$(RM) *.o *.a main
