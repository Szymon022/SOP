CC=gcc
CFLAGS=-Wall -fsanitize=address,undefined

all: prog
prog: prog.c
	${CC} ${CFLAGS} -o prog prog.c
.PHONY:
	clean all
clean:
	rm -f prog