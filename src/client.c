/*
 * client.c
 *
 * Copyright (c) 2017, 2018 Martijn
 * Released under the MIT License
 */

#include "client.h"
#include "util.h"
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

    if (getaddrinfo(host, port, &hints, &res) != 0) {
        printerr("Error resolving host information\n");
        return -1;
    }

    sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
    if (sockfd < 0) {
        printerr("Error opening socket");
        return -1;
    }

    printf("Connecting to %s:%s...", host, port);
    if (connect(sockfd, res->ai_addr, res->ai_addrlen) < 0) {
        printerr("Could not connect to %s", host);
        return -1;
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
    if (s_sec == 0) {
        printerr("Error exchaning keys\n");
        return -1;
    }
    printf("Shared secret key: %d\n", s_sec);

    close(sockfd);
    printf("Connection closed.\n");
    return 0;
}

int main(int argc, char *argv[])
{
    return client(argv[1], argv[2]);
}
