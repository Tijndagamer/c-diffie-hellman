/*
 * client.c
 *
 * Copyright (c) 2017, 2018 Martijn
 * Released under the MIT License
 */

#include "client.h"
#include "diffiehellman.h"

int client(char *port, char *host)
{
    int sockfd, n;
    struct sockaddr_in s_addr;
    struct hostent *server;
    struct addrinfo hints, *res;

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    if (getaddrinfo(host, port, &hints, &res) != 0)
        printf("Error resolving host information\n");

    sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
    if (sockfd < 0) {
        printf("Error opening socket");
        exit(1);
    }

    printf("Connecting to %s:%s...", host, port);
    if (connect(sockfd, res->ai_addr, res->ai_addrlen) < 0) {
        printf("Could not connect to %s", host);
        exit(1);
    }
    printf("done.\n");

    // We're connected, so the diffie-hellman magic can start!
    int p, g;
    recv_int(sockfd, &p);
    recv_int(sockfd, &g);
    printf("Agreed on p: %d\t g: %d\n", p, g);
    int s_sec;
    int p_sec = 4;
    s_sec = diffiehellman_c(sockfd, p, g, p_sec);
    printf("Shared secret key: %d\n", s_sec);

    close(sockfd);
    printf("Connection closed.\n");
}

int main(int argc, char *argv[])
{
    client(argv[1], argv[2]);
    return 0;
}
