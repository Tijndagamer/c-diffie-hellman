/*
 * util.h
 *
 * Copyright (c) 2018 Martijn
 * Licensed under the MIT License
 */

#ifndef UTIL_h
#define UTIL_h

#include <unistd.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdarg.h>

/*
 * Send and receive integers via sockets
 */
int send_int(int fd, int i);
int recv_int(int fd, int *i);

/*
 * Print error to stderr
 */
void printerr(const char *format, ...);

#endif
