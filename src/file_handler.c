#include "file_handler.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define BUFFER_SIZE 104857600

void read_file(const char *filename, char *buffer) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    rewind(file);

    if (file_size >= BUFFER_SIZE) {
        perror("File size exceeds buffer size");
        exit(EXIT_FAILURE);
    }

    size_t bytes_read = fread(buffer, sizeof(char), file_size, file);
    if (bytes_read != file_size) {
        perror("Error reading file");
        exit(EXIT_FAILURE);
    }

    buffer[bytes_read] = '\0'; 

    fclose(file);
}
