#include "./inc/reader.h"

_Bool read_bytecode(const char *source, input_fn processor)
{
    FILE *file = fopen(source, "r");

    if (file == NULL)
        return 0;

    int current;
    while ((current = fgetc(file)) != EOF)
    {
        int out = processor((uint8_t)current);
        if (out < 0)
        {
            fclose(file);
            return 0;
        }
    }

    fclose(file);
    return 1;
}