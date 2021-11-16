all: prog5
prog5: prog5.c
	gcc -Wall -fsanitize=address,undefined -o prog5 prog5.c

.PHONY:
	clean all
	
clean:
	rm -f prog5