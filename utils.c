#include <stdlib.h>
#include <stdio.h>

void checkMalloc(void *data) {
    if (data == NULL) {
        printf("Memory allocation FAILED. Exiting...");
        free(data);
        exit(0);
    }
}

void checkFile(FILE *file) {
    if (file == NULL) {
        printf("The input file was not found. Exiting...");
        exit(0);
    }
}