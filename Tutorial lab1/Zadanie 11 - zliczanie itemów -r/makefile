all: prog11
prog11:prog11.c
	gcc -Wall -fsanitize=address,undefined -o prog11 prog11.c
.PHONY:
	clean all
clean:
	rm prog11