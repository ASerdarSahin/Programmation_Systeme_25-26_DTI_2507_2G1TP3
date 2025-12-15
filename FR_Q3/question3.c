#include <string.h>
#include "question3.h"

int is_exit_command(char *buffer)
{
    return (strncmp(buffer, "exit", 4) == 0);
}
