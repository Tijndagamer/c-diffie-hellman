/*
 * server.c
 *
 * Copyright (c) 2017, 2018 Martijn
 * Released under the MIT License
 */

#include "server.h"

int server(char *port)
{
    int sockfd, conn_sockfd;
    int client_len;
    int n;
    char buffer[256];
    char cl_ip[INET_ADDRSTRLEN];
    struct sockaddr_in cl_addr;
    struct addrinfo hints, *res;

    printf("Starting c-socket server...\n");

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET; // TODO: Add IPv6 support
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    if (getaddrinfo(NULL, port, &hints, &res) != 0)
        printf("Error getaddrinfo\n");

    sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
    if (sockfd < 0)
        printf("Error opening socket\n");

    if (bind(sockfd, res->ai_addr, res->ai_addrlen) < 0)
        printf("Error binding to socket\n");

    listen(sockfd, 5);

    while (1) {
        bzero(buffer, 256);
        client_len = sizeof(cl_addr);

        conn_sockfd = accept(sockfd, (struct sockaddrr *) &cl_addr, &client_len);
        if (conn_sockfd < 0)
            printf("Error accepting connection");
        inet_ntop(AF_INET, &(cl_addr.sin_addr), cl_ip, INET_ADDRSTRLEN);
        printf("Accepted connection from %s:%d\n", cl_ip, cl_addr.sin_port);

        n = read(conn_sockfd, buffer, 255);
        printf("%s\n", buffer);

        close(conn_sockfd);
        printf("Connection closed\n");
    }
}

int main(int argc, char *argv[])
{
    server(argv[1]);
    return 0;
}
