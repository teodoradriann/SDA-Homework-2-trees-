#include <stdlib.h>
#include <stdio.h>

void checkMalloc(void *data) {
    if (data == NULL) {
        printf("Memory allocation FAILED. Exiting...");
        free(data);
        exit(0);
    }
}
