/*
 * server.c
 *
 * Copyright (c) 2017, 2018 Martijn
 * Released under the MIT License
 */

#include "server.h"
#include "diffiehellman.h"

int server(char *port)
{
    int sockfd, conn_sockfd;
    int client_len;
    char cl_ip[INET_ADDRSTRLEN];
    struct sockaddr_in cl_addr;
    struct addrinfo hints, *res;

    printf("Starting c-socket server...\n");

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET; // TODO: Add IPv6 support
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    if (getaddrinfo(NULL, port, &hints, &res) != 0) {
        printf("Error getaddrinfo\n");
        return -1;
    }

    sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
    if (sockfd < 0) {
        printf("Error opening socket\n");
        return -1;
    }

    if (bind(sockfd, res->ai_addr, res->ai_addrlen) < 0) {
        printf("Error binding to socket\n");
        return -1;
    }

    listen(sockfd, 5);

    while (1) {
        client_len = sizeof(cl_addr);

        conn_sockfd = accept(sockfd, (struct sockaddrr *) &cl_addr, &client_len);
        if (conn_sockfd < 0) {
            printf("Error accepting connection");
            return -1;
        }
        inet_ntop(AF_INET, &(cl_addr.sin_addr), cl_ip, INET_ADDRSTRLEN);
        printf("Accepted connection from %s:%d\n", cl_ip, cl_addr.sin_port);

        // Now that we're connected, we can exchange keys.
        int p = 11;
        int g = 2;
        int n1, n2;
        n1 = send_int(conn_sockfd, p);
        n2 = send_int(conn_sockfd, g);
        if (n1 < 0 && n2 < 0) {
           printf("Error sending parameters!\n");
           return -1;
        }
        printf("Agreed on p: %d\t g: %d\n", p, g);
        int s_sec;
        int p_sec = 3;
        s_sec = diffiehellman_s(conn_sockfd, p, g, p_sec);
        printf("Shared secret key: %d\n", s_sec);

        close(conn_sockfd);
        printf("Connection closed\n");
    }
    return 0;
}

int main(int argc, char *argv[])
{
    return server(argv[1]);
}
