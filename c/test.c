#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 1024

extern void create_socket();
extern void create_http_response(char *buffer, char *body);
extern void create_404_response(char *buffer);
extern void create_health_response(char *buffer);

void test_create_http_response() {
  printf("test_create_http_response\n");
  printf("============================================================\n");

  char body[BUFFER_SIZE];
  create_health_response(body);
  char buffer[BUFFER_SIZE];
  create_http_response(buffer, body);

  printf("http response: %s\n\n", buffer);
}

void test_create_404_response() {
  printf("test_create_404_response\n");
  printf("============================================================\n");

  char buffer[BUFFER_SIZE];
  create_404_response(buffer);

  printf("404 response: %s\n\n", buffer);
}

void test_create_health_response() {
  printf("test_create_health_response\n");
  printf("============================================================\n");

  char buffer[BUFFER_SIZE];
  create_health_response(buffer);

  printf("health response: %s\n\n", buffer);
}

int test() {
  printf("testing...\n\n");
  test_create_health_response();
  test_create_http_response();
  test_create_404_response();
  printf("done all tests\n");
  return 0;
}
