#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/un.h>
#include <unistd.h>
#define MAX_QUEUE_CONNECTIONS 250
int main() {
  printf("Server Code \n");
  char port[50];
  char path[50] = "http.html";
  char permission = 'r';
  struct addrinfo hint, *res;
  // struct sockaddr_un recieve_server,hint;
  memset(&hint, 0, sizeof(hint));
  hint.ai_family = AF_INET;
  hint.ai_socktype = SOCK_STREAM;
  hint.ai_flags = AI_PASSIVE;
  socklen_t recieve_len;
  int server_fd = socket(hint.ai_family, hint.ai_socktype, 0);
  if (server_fd >= 0) {
    printf("Successfully created socket : %d\n", server_fd);

  } else {
    printf("Not able to create the socket : %d\n", server_fd);
  }
  // this is just to modify the sockaddr struct which should not be updated
  // directly and its instance can only be updated
  int addr_set = getaddrinfo(NULL, "8080", &hint, &res);
  // hint.sun_family=AF_INET;
  // int i=0;
  // char *ptr=port;
  // while(*hint.sun_path !='\0'){
  //   *port=*hint.sun_path;
  //   *port+=1;
  //   *hint.sun_path+=1;
  // }
  // *port = '\0';
  int yes = 1;
  setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes));
  int bind_server = bind(server_fd, res->ai_addr, res->ai_addrlen);
  if (bind_server >= 0) {
    printf("Binded succesfully to the server : %d\n", bind_server);
  } else {
    printf("Error in binding with the server : %d \n", bind_server);
  }
  int listen_connections = listen(server_fd, 20);
  if (listen < 0) {
    printf("Error listening \n");
    exit(-1);
  }
  struct sockaddr_storage their_addr;
  socklen_t addrsize;
  int new_fd = accept(server_fd, (struct sockaddr *)&their_addr, &addrsize);
  if (new_fd < 0) {
    perror("Error in accepting ");
    exit(-1);
  }
  int max_length = 1000;
  char buffer[max_length];
  int recieved_bytes = recv(new_fd, buffer, max_length, 0);
  printf("Bytes recieved : %d\n", recieved_bytes);
  int buffer_length = sizeof(buffer) / buffer[0];
  for (int i = 0; i < recieved_bytes; i++) {
    putchar(buffer[i]);
  }
  char status_line[100] = "HTTP/1.1 200 OK \r\n";
  char headers[100] = "Content-Type: text/html\r\n\r\n";
  char body[100] =
      "<html><body><h1>Hello Client u are cooked </h1></body></html>\r\n";
  FILE *fd = fopen("./src/http.html", "r");
  if (fd == NULL) {
    perror("Error in file opening");
  }
  int a = send(new_fd, status_line, strlen(status_line), 0);
  int b = send(new_fd, headers, strlen(headers), 0);
  char file_char;
  while ((file_char = getc(fd)) != EOF) {
    // putchar(file_char);
    send(new_fd, &file_char, 1, 0);
  }

  // int c =send(new_fd,body,strlen(body),0);
  if (a != -1) {
    printf("Sent the status line number of bytes : %d\n", a);
    // printf("Sent the header content of size : %d\n",b);
  } else {
    printf("Error sending the status line \n");
    // close(server_fd);
    // close(new_fd);
  }

  // int act_listener =listen(server_fd,MAX_QUEUE_CONNECTIONS);
  // if(act_listener>=0){
  //   printf("Succesfully set up the server and listening ... \n");
  // }else {
  //   printf("Error setting up as listener : %d ",act_listener);
  // }
  //
  // int accept_fd=accept(server_fd,(struct sockaddr
  // *)&recieve_server,&recieve_len); if(accept_fd>=0){
  //   printf("Succesfully accepting messages from fd \n");
  //
  // }else {
  //   printf("Error in accepting : %d ",accept_fd);
  // }
  return 0;
}
