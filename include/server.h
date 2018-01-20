/*
 * server.h
 *
 * Copyright (c) 2018 Martijn
 * Released under the MIT License
 */

#ifndef SERVER_h
#define SERVER_h

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdbool.h>
#include <netdb.h>

int server(char *port);
int main(int argc, char *argv[]);

#endif

