all: prog7
prog7: prog7.c
	gcc -Wall -fsanitize=address,undefined prog7.c -o prog7

.PHONY:
	clean all

clean:
	rm -f prog7