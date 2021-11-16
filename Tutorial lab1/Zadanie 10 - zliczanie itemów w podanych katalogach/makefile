all: prog10
prog10: prog10.c
	gcc -Wall -fsanitize=address,undefined -o prog10 prog10.c
	
.PHONY:
	clean all

clean:
	rm -f prog10