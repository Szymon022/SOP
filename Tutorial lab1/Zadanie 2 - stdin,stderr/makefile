all: prog2
prog2: prog2.c
	gcc -Wall -fsanitize=address,undefined -o prog2 prog2.c

.PHONY:
	clean all

clean:
	rm -f prog2