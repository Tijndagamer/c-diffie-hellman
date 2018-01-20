/*
 * client.h
 *
 * Copyright (c) 2018 Martijn
 * Released under the MIT License
 */

#ifndef CLIENT_h
#define CLIENT_h

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <unistd.h>
#include <stdbool.h>

int client(char *port, char *host);
int main(int argc, char *argv[]);

#endif
