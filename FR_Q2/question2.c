#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "question2.h"
#include "question5.h"
#include "question6.h"
#include "question7.h"

ssize_t read_command(char *buffer, size_t size)
{
    return read(STDIN_FILENO, buffer, size);
}

void execute_simple_command(char *buffer)
{
    pid_t pid;
    int status;
    struct timespec start, end;

    clock_gettime(CLOCK_MONOTONIC, &start);

    pid = fork();

    if (pid == 0)
    {
        char **args = parse_arguments(buffer);
        if (args == NULL)
            _exit(0);

	handle_redirections(args);
        execvp(args[0], args);
        _exit(1);
    }
    else
    {
        waitpid(pid, &status, 0);
        clock_gettime(CLOCK_MONOTONIC, &end);

        long time_ms = compute_time_ms(start, end);

        char msg[64];
        int len;

        if (WIFEXITED(status))
        {
            len = snprintf(msg, sizeof(msg),
                           "[exit:%d|%ldms] ",
                           WEXITSTATUS(status), time_ms);
        }
        else if (WIFSIGNALED(status))
        {
            len = snprintf(msg, sizeof(msg),
                           "[sign:%d|%ldms] ",
                           WTERMSIG(status), time_ms);
        }
        write(STDOUT_FILENO, msg, len);
    }
}


