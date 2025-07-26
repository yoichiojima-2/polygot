#include <stdio.h>
#include <string.h>

#define VERSION "0.1.0"
#define BUFFER_SIZE 1000

void create_http_response_with_status(char *buffer, const char *status_list,
                                      const char *body) {
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
  create_http_response_with_status(buffer, "200 OK", body);
}

void create_404_response(char *buffer) {
  create_http_response_with_status(buffer, "404 Not Found", "{\"error\": \"not found\"}");
}

void create_health_response(char *buffer) {
  char body[BUFFER_SIZE];
  snprintf(body, BUFFER_SIZE, "{\"language\": \"c\", \"version\": \"%s\"}",
           VERSION);
  create_http_response_with_status(buffer, "200 OK", body);
}

int main(int argc, char *argv[]) {
  char body[BUFFER_SIZE];
  char buffer[BUFFER_SIZE];
  create_health_response(body);
  create_http_response(buffer, body);
  printf("http response: %s\n", buffer);
  return 0;
};

