#include <stdio.h>
#include <string.h>

#define FUNCTIONS_H

#define VERSION "0.1.0"
#define BUFFER_SIZE 1000

void create_health_response(char *buffer) {
  snprintf(buffer, BUFFER_SIZE, "{\"language\": \"c\", \"version\": \"%s\"}",
           VERSION);
}

int main() {
  char buffer[BUFFER_SIZE];

  create_health_response(buffer);
  printf("health response: %s\n", buffer);

  return 0;
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