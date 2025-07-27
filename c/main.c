#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define VERSION "0.1.0"
#define BUFFER_SIZE 1000
#define HTTP_200 "200 OK\r\n"
#define HTTP_404 "404 Not Found\r\n"
#define PORT 8080

int create_socket() {
  int server_socket = socket(AF_INET, SOCK_STREAM, 0);
  int opt = 1;
  if (setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) >
      0) {
    perror("setsockopt failed");
    close(server_socket);
    exit(EXIT_FAILURE);
  }
  return server_socket;
}

void add_http_headers(char *buffer, const char *status_list, const char *body) {
  snprintf(buffer, BUFFER_SIZE,
           "HTTP/1.1 %s\r\n"
           "Content-Type: application/json\r\n"
           "Content-Length: %zu\r\n"
           "Access-Control-Allow-Origin: *\r\n"
           "Connection: close\r\n"
           "\r\n"
           "%s",
           status_list, strlen(body), body);
}

void create_http_response(char *buffer, char *body) {
  add_http_headers(buffer, HTTP_200, body);
}

void create_404_response(char *buffer) {
  add_http_headers(buffer, HTTP_404, "{\"error\": \"not found\"}");
}

void create_health_response(char *buffer) {
  char body[BUFFER_SIZE];
  snprintf(body, BUFFER_SIZE, "{\"language\": \"c\", \"version\": \"%s\"}",
           VERSION);
  add_http_headers(buffer, HTTP_200, body);
}

struct sockaddr_in create_server_addr() {
  struct sockaddr_in server_addr;
  server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = INADDR_ANY;
  server_addr.sin_port = htons(PORT);
  return server_addr;
}

void bind_socket(int server_socket, struct sockaddr_in *server_addr) {
  if (bind(server_socket, (struct sockaddr *)server_addr,
           sizeof(*server_addr)) < 0) {
    perror("bind failed");
    close(server_socket);
    exit(EXIT_FAILURE);
  }
}

void listen_socket(int server_socket) {
  if (listen(server_socket, 3) < 0) {
    perror("listen failed");
    close(server_socket);
    exit(EXIT_FAILURE);
  }
}

void handle_client(int client_socket) {
  char buffer[BUFFER_SIZE] = {0};
  char response[BUFFER_SIZE] = {0};

  read(client_socket, buffer, BUFFER_SIZE);

  if (strstr(buffer, "GET /health") != NULL) {
    create_health_response(response);
  } else {
    create_404_response(response);
  }

  write(client_socket, response, strlen(response));
  close(client_socket);
}

int create_client_socket(int server_socket) {
  struct sockaddr_in client_addr;
  socklen_t client_addr_len = sizeof(client_addr);
  int client_socket =
      accept(server_socket, (struct sockaddr *)&client_addr, &client_addr_len);
  return client_socket;
}

void serve() {
  int server_socket = create_socket();
  struct sockaddr_in server_addr = create_server_addr();
  bind_socket(server_socket, &server_addr);
  listen_socket(server_socket);
  printf("server running on port %d\n", PORT);

  while (1) {
    int client_socket = create_client_socket(server_socket);
    if (client_socket < 0) {
      perror("accept failed");
      continue;
    }
    handle_client(client_socket);
  }

  close(server_socket);
}

int main(int argc, char *argv[]) {
  if (argc > 1 && strcmp(argv[1], "test") == 0) {
    extern int test();
    return test();
  }
  serve();
  return 0;
}
