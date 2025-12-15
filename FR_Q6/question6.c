#include <stdlib.h>
#include <string.h>
#include "question6.h"

char **parse_arguments(char *buffer)
{
    static char *args[64];
    int i = 0;

    buffer[strcspn(buffer, "\n")] = 0;
    args[i++] = strtok(buffer, " ");

    while ((args[i++] = strtok(NULL, " ")) != NULL);

    return args;
}
