#include "functions.h"
#include <stdio.h>

void create_health_response(char *buffer) {
    snprintf(buffer, BUFFER_SIZE, "{\"language\": \"c\", \"version\": \"%s\"}", VERSION);
}
