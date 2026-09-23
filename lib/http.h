#ifndef HTTP_FILE_H
#define HTTP_FILE_H
#include <netdb.h>
#include <stdio.h>
#include <sys/socket.h>

typedef struct {
  int socket_fd;
  int new_socket_fd;
  struct addrinfo *result_info;
} sock;

extern sock legit_sock;

#endif
