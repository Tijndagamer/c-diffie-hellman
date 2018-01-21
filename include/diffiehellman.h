/*
 * diffie-hellman.h
 *
 * Copyright (c) 2018 Martijn
 * Licensed under the MIT License
 */

#ifndef DH_h
#define DH_h

#include <math.h>
#include <arpa/inet.h>
#include <unistd.h>

/*
 * Perform a diffie-hellman key exchange on the connected socket with sockfd.
 * p and g are the prime and base on which the client and server have already
 * agreed.
 * isec is our secret integer.
 */
int diffiehellman(int sockfd, int p, int g, int isec);

/*
 * Send and receive integers via sockets
 */
int send_int(int fd, int i);
int recv_int(int fd, int *i);

#endif
