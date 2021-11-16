all: prog9
prog9: prog9.c
	gcc -Wall -fsanitize=address,undefined prog9.c -o prog9
.PHONY:
	clean all
clean:
	rm -f prog9