CC = gcc
LIBS = -lblkid

all:
	$(CC)  -o main.o  src/main.c $(LIBS) -std=c11

start:
	./main.o --first

clear:
	rm -rf *.o