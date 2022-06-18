FILE = C-Programs/FCFS.c
PROG = build/FCFS

CC = gcc
CFLAGS = -Wall -o

${PROG}: ${FILE}
	${CC} ${CFLAGS} ${PROG} ${FILE}

run: ${PROG}
	./${PROG}

clean: ${PROG}
	rm ${PROG}
