#include <stdio.h>

#define VERSION "0.1.0"
#define BUFFER_SIZE 1000

// create json response
void create_health_response(char* buffer) {
    snprintf(
        buffer,
        BUFFER_SIZE,
        "{\"language\": \"c\", \"version\": \"%s\"}",
        VERSION
    );
}

int main() {
    char buffer[BUFFER_SIZE];

    create_health_response(buffer);
    printf("health response: %s\n", buffer);

    return 0;
}
