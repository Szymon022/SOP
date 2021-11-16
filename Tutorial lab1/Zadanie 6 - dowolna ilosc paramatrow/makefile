all: prog6
prog6: prog6.c
	gcc -Wall -fsanitize=address,undefined -o prog6 prog6.c

.PHONY:
	clean all

clean:
	rm -f prog6