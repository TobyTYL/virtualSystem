CC = gcc
CFAGS = -Wall

vfs: main.o filesystem.o utils.o
	$(CC) $(CFLAGS) -o $@ $^

filesystem.o: filesystem.c
	$(CC) $(CFLAGS) -c filesystem.c -o filesystem.o

main.o: main.c
	$(CC) $(CFLAGS) -c main.c -o main.o

utils.o: utils.c
	$(CC) $(CFLAGS) -c $^ -o $@

clean:
	rm -f *.o vfs

valgrind: 
	valgrind --leak-check=full ./vfs





# vfs: main.o filesystem.o
# 	$(CC) -Wall -o $@ $^

# filesystem.o: filesystem.c
# 	$(CC) -Wall -c filesystem.c -o filesystem.o
# main.o: main.c
# 	gcc -Wall -c main.c -o main.o

# clean:
# 	rm -f *.o vfs

# valgrind:
# 	valgrind --leak-check=full ./vfs
