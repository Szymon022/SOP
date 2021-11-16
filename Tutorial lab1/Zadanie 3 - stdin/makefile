all: prog3
prog3: prog3.c
	gcc -Wall -fsanitize=address,undefined -o prog3 prog3.c

.PHONY:
	clean all

clean:
	rm -f prog3