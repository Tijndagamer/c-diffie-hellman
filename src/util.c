/*
 * util.c
 *
 * Copyright (c) 2018 Martijn
 * Licensed under the MIT License
 */

#include "util.h"

/*
 * Send i via socket fd.
 */
int send_int(int fd, int i)
{
    int32_t conv = htonl(i);
    char *data = (char *)&conv;
    int left = sizeof(conv);
    int rc;
    do {
        rc = write(fd, data, left);
        if (rc == -1) {
            return -1;
        } else {
            data += rc;
            left -= rc;
        }
    } while (left > 0);
    return 0;
}

/*
 * Receive integer from socket fd to i.
 */
int recv_int(int fd, int *i)
{
    int32_t ret;
    char *data = (char *)&ret;
    int left = sizeof(ret);
    int rc;
    do {
        rc = read(fd, data, left);
        if (rc <= 0) {
            return -1;
        } else {
            data += rc;
            left -= rc;
        }
    } while (left > 0);
    *i = ntohl(ret);
    return 0;
}

/*
 * Print error to stderr
 */
void printerr(const char *format, ...)
{
    va_list args;
    va_start(args, format);
    vfprintf(stderr, format, args);
    va_end(args);
}
