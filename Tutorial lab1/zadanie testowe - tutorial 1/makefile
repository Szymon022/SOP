all: prog
prog: prog.c
	gcc -Wall -fsanitize=address,undefined -o prog prog.c
.PHONY:
	clean all
clean:
	rm -f prog