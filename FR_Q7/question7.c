#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include "question7.h"

void handle_redirections(char **args)
{
    for (int i = 0; args[i]; i++)
    {
        if (strcmp(args[i], ">") == 0)
        {
            int fd = open(args[i+1], O_CREAT|O_TRUNC|O_WRONLY, 0644);
            dup2(fd, STDOUT_FILENO);
            close(fd);
            args[i] = NULL;
        }
        if (strcmp(args[i], "<") == 0)
        {
            int fd = open(args[i+1], O_RDONLY);
            dup2(fd, STDIN_FILENO);
            close(fd);
            args[i] = NULL;
        }
    }
}
