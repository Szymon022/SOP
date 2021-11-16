TARGET=prog8
C_FILE=${TARGET}.c

all: ${TARGET}
${TARGET}: ${C_FILE}
	gcc -Wall -fsanitize=address,undefined -o ${TARGET} ${C_FILE}

.PHONY:
	clean all

clean:
	rm -f ${TARGET}
