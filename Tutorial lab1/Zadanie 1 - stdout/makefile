all: prog1
prog1: prog1.c
	gcc -Wall -fsanitize=address,undefined prog1.c -o prog1

.PHONY:
	clean all

clean:
	rm prog1