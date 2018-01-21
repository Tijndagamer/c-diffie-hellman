/*
 * diffie-hellman.c
 *
 * Copyright (c) 2018 Martijn
 * Licensed under the MIT License
 */

#include "diffiehellman.h"
#include "util.h"

/*
 * Perform a diffie-hellman key exchange.
 */
int diffiehellman_s(int sockfd, int p, int g, int p_sec)
{
    if (is_prime(p) == 0)
        return 0;

    int a = ((int)pow(g, p_sec)) % p;
    send_int(sockfd, a);
    int b;
    recv_int(sockfd, &b);

    return ((int)pow(b, p_sec)) % p;
}

int diffiehellman_c(int sockfd, int p, int g, int p_sec)
{
    if (is_prime(p) == 0)
        return 0;

    int a;
    recv_int(sockfd, &a);
    int b = ((int)pow(g, p_sec)) % p;
    send_int(sockfd, b);

    return ((int)pow(a, p_sec)) % p;
}

/*
 * Return 1 if n is a prime
 */
int is_prime(unsigned int n)
{
    if (n <= 1) {
        return 0;
    } else if (n == 2 || n == 3) {
        return 1;
    } else if (n % 2 == 0 || n % 3 == 0) {
        return 0;
    } else {
        for (unsigned int i = 5; i*i <= n; i += 6) {
            if (n % i == 0 || n % (i + 2) == 0)
                return 0;
        }
        return 1;
    }
}
