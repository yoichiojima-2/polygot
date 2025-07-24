#include "main.h"

int main() {
  char buffer[BUFFER_SIZE];

  create_health_response(buffer);
  printf("health response: %s\n", buffer);

  return 0;
}
