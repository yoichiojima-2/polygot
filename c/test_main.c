#include "functions.h"
#include <stdio.h>
#include <string.h>

void test_create_health_response() {
    char buffer[BUFFER_SIZE];
    create_health_response(buffer);
    if (strcmp(buffer, "{\"language\": \"c\", \"version\": \"0.1.0\"}") == 0) {
        printf("test_create_health_response: PASSED\n");
    } else {
        printf("test_create_health_response: FAILED\n");
    }
}

int main() {
  char buffer[BUFFER_SIZE];
  test_create_health_response();
  return 0;
}
