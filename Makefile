CC = gcc
VPATH = src
CFLAGS = -Iinclude -g
HEADERS = $(wildcard include/*.h)
SRC = $(wildcard src/*.c)
SRC_SHARED = src/diffiehellman.c
SRC_C = src/client.c $(SRC_SHARED)
SRC_S = src/server.c $(SRC_SHARED)
OBJ = client.o server.o
EXEC_S = server
EXEC_C = client

client :
	$(CC) $(CFLAGS) $(SRC_C) -lm -o $(EXEC_C)

server :
	$(CC) $(CFLAGS) $(SRC_S) -lm -o $(EXEC_S)

clean : 
	-rm $(EXEC_C) $(EXEC_S) $(OBJ)
