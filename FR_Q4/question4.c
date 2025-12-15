#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <stdio.h>
#include "question4.h"

void print_exit_status(int status)
{
    char buf[64];

    if (WIFEXITED(status))
        snprintf(buf, sizeof(buf), "[exit:%d] ", WEXITSTATUS(status));
    else if (WIFSIGNALED(status))
        snprintf(buf, sizeof(buf), "[sign:%d] ", WTERMSIG(status));

    write(STDOUT_FILENO, buf, strlen(buf));
}
