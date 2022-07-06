FILE = C-Programs/Fork.c
PROG = build/Fork

CC = gcc
CFLAGS = -Wall -o

${PROG}: ${FILE}
	${CC} ${CFLAGS} ${PROG} ${FILE}

run: ${PROG}
	./${PROG}

clean: ${PROG}
	rm ${PROG}
