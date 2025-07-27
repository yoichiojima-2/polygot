#include <stdio.h>
#include <string.h>

#define VERSION "0.1.0"
#define BUFFER_SIZE 1000
#define HTTP_200 "200 OK\r\n"
#define HTTP_404 "404 Not Found\r\n"

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
  create_http_response_with_status(buffer, HTTP_200, body);
}

void create_404_response(char *buffer) {
  create_http_response_with_status(buffer, HTTP_404, "{\"error\": \"not found\"}");
}

void create_health_response(char *buffer) {
  char body[BUFFER_SIZE];
  snprintf(body, BUFFER_SIZE, "{\"language\": \"c\", \"version\": \"%s\"}",
           VERSION);
  create_http_response_with_status(buffer, HTTP_200, body);
}

int main(int argc, char *argv[]) {
  if (argc > 1 && strcmp(argv[1], "test") == 0) {
    extern int test();
    return test();
  }

  char body[BUFFER_SIZE];
  char buffer[BUFFER_SIZE];
  create_health_response(body);
  create_http_response(buffer, body);
  printf("http response: %s\n", buffer);
  return 0;
};

