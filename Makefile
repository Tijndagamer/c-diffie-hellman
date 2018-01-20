CC = gcc
VPATH = src
CFLAGS = -I include
HEADERS = $(wildcard include/*.h)
SRC = $(wildcard src/*.c)
OBJ = client.o server.o
EXEC_S = server
EXEC_C = client

client :
	$(CC) $(CFLAGS) src/client.c -o $(EXEC_C)

server :
	$(CC) $(CFLAGS) src/server.c -o $(EXEC_S)

clean : 
	-rm $(EXEC_C) $(EXEC_S) $(OBJ)
