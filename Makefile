## Makefile

CC     = gcc
CFLAGS = -g3 -std=gnu99 -pedantic -Wall

Scheduler:  Scheduler.o
	${CC} ${CFLAGS} -o Scheduler Scheduler.o

Scheduler.o: Scheduler.c
	${CC} ${CFLAGS} -c Scheduler.c
