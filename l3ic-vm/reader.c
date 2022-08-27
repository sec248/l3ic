#include "reader.h"

read_result *read_source(char *path) {
    size_t length;

    FILE *file = fopen(path, "rb");
    if (file == NULL) {
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    length = ftell(file);
    rewind(file);

    read_result *data = calloc(1, sizeof(read_result));
    if (data == NULL) {
        fclose(file);
        return NULL;
    }

    data->memory = calloc(length + 1, sizeof(uint8_t));
    data->length = length;

    if (data->memory == NULL) {
        fclose(file);
        free(data);
        return NULL;
    }
    
    fread(data->memory, length * sizeof(uint8_t), 1, file);
    fclose(file);

    return data;
}
