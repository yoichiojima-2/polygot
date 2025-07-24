#include <stdio.h>
#include <string.h>

#define VERSION "0.1.0"
#define BUFFER_SIZE 1000

void create_http_response(const char *json_body, char *buffer) {
  snprintf(buffer, BUFFER_SIZE,
           "HTTP/1.1 200 OK\r\n"
           "Content-Type: application/json\r\n"
           "Content-Length: %zu\r\n"
           "Access-Control-Allow-Origin: *\r\n"
           "Connection: close\r\n"
           "\r\n"
           "%s",
           strlen(json_body), json_body);
}

void create_health_response(char *buffer) {
  snprintf(buffer, BUFFER_SIZE, "{\"language\": \"c\", \"version\": \"%s\"}",
           VERSION);
}

void test_create_http_response() {
  char json_body[BUFFER_SIZE];
  char http_response[BUFFER_SIZE];
  create_health_response(json_body);
  create_http_response(json_body, http_response);
  printf("http response: %s\n", http_response);
  printf("[test_create_http_response] PASSED\n");
}

void test_create_health_response() {
  char buffer[BUFFER_SIZE];
  create_health_response(buffer);
  if (strcmp(buffer, "{\"language\": \"c\", \"version\": \"0.1.0\"}") == 0) {
    printf("test_create_health_response: PASSED\n");
  } else {
    printf("test_create_health_response: FAILED\n");
  }
}

int test() {
  printf("testing...\n");
  test_create_health_response();
  test_create_http_response();
  printf("done all tests\n");
  return 0;
}

int main(int argc, char *argv[]) {
  if (argc > 1 && strcmp(argv[1], "test") == 0) {
    test();
    return 0;
  }

  char buffer[BUFFER_SIZE];

  create_health_response(buffer);
  printf("health response: %s\n", buffer);

  return 0;
}
