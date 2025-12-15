#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include "question6.h"
#include "question7.h"
#include "question8.h"

void execute_pipe(char *buffer)
{
    int fd[2];
    pid_t pid1, pid2;
    char *cmd1;
    char *cmd2;

    cmd1 = strtok(buffer, "|");
    cmd2 = strtok(NULL, "|");

    if (!cmd2)
        return;

    pipe(fd);

    /* Premier fils : écrit dans le pipe */
    pid1 = fork();
    if (pid1 == 0)
    {
        dup2(fd[1], STDOUT_FILENO);
        close(fd[0]);
        close(fd[1]);

        char **args1 = parse_arguments(cmd1);
        handle_redirections(args1);
        execvp(args1[0], args1);
        _exit(1);
    }

    /* Second fils : lit depuis le pipe */
    pid2 = fork();
    if (pid2 == 0)
    {
        dup2(fd[0], STDIN_FILENO);
        close(fd[1]);
        close(fd[0]);

        char **args2 = parse_arguments(cmd2);
        handle_redirections(args2);
        execvp(args2[0], args2);
        _exit(1);
    }

    close(fd[0]);
    close(fd[1]);

    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);
}
