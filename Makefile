
CC = gcc
CFLAGS = -Wall




vfs: main.o filesystem.o utils.o
	$(CC) -Wall -o $@ $^

filesystem.o: filesystem.c
	$(CC) -Wall -c filesystem.c -o filesystem.o
main.o: main.c
	gcc -Wall -c main.c -o main.o
utils.o: utils.c
	$(CC) -Wall -c $^ -o $@
clean:
	rm -f *.o vfs

valgrind:
	valgrind --leak-check=full ./vfs
