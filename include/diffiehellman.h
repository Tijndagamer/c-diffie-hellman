/*
 * diffie-hellman.h
 *
 * Copyright (c) 2018 Martijn
 * Licensed under the MIT License
 */

#ifndef DH_h
#define DH_h

#include <math.h>
#include <unistd.h>

/*
 * Perform a diffie-hellman key exchange on the connected socket with sockfd.
 * p and g are the prime and base on which the client and server have already
 * agreed.
 * p_sec is our private secret integer.
 */
int diffiehellman_c(int sockfd, int p, int g, int p_sec);
int diffiehellman_s(int sockfd, int p, int g, int p_sec);

/*
 * We need to be sure that the supplied p in the diffie-hellman key exchange
 * is a prime; we will check that using this function.
 */
int is_prime(unsigned int n);

#endif
