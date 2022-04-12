CFLAGS=-Wall -Wextra -Wdouble-promotion -Wconversion -Wsign-conversion

all: cliente servidor

$cliente : cliente.c
	gcc $(CFLAGS) -o $@ $^

$servidor: servidor.c
	gcc $(CFLAGS) -o $@ $^

