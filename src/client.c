#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

int main() {
  printf("Client side code \n");
  // int server_fd = legit_sock.socket_fd;
  int client_fd = socket(AF_INET, SOCK_STREAM, 0);
  printf("%d\n", client_fd);
  if (client_fd < 0) {
    perror("Unable to connect to the server fd");
  }
  // int real_fd = legit_sock.new_socket_fd;
  struct addrinfo hint = {0};
  struct addrinfo *res = {0};
  hint.ai_family = AF_INET;
  hint.ai_socktype = SOCK_STREAM;
  hint.ai_flags = AI_PASSIVE;
  int addr_set = getaddrinfo("127.0.0.1", "8080", &hint, &res);
  printf("Address set : %d ", addr_set);
  if (addr_set < 0) {
    perror("Error in setting the values of port and ip");
  }
  int connect_thing = connect(client_fd, res->ai_addr, res->ai_addrlen);
  printf("Connection thing : %d\n", connect_thing);
  if (connect_thing < 0) {
    perror("Error in connecting to the server ");
  }
  char status_line[100] = "GET / HTTP/1.1 \r\n";
  char host[100] = "Host: localhost:8080 \r\n";
  // char headers[100] = "Content-Type: text/html\r\n\r\n";
  // char data[200] = "<html><body><h1>Hello server , I am Dhanush Poduval "
  //                  "</h1></body></html>\r\n";
  int send_status = send(client_fd, status_line, strlen(status_line), 0);
  int send_address = send(client_fd, host, strlen(host), 0);
  if (send_status < 0) {
    perror("Error in sendind status");
  }
  if (send_address < 0) {
    perror("Error in sending the address and port details ");
  }
  char rec_data[500];
  int recive_data = recv(client_fd, rec_data, 500, 0);
  for (int i = 0; i < recive_data; i++) {
    putchar(rec_data[i]);
  }
  return 0;
}
