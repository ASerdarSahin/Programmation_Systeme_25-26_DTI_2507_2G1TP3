#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/resource.h>
#include <stdio.h>
#include "question6.h"
#include "question9.h"

static bg_process_t *bg_list = NULL;

void launch_background(char *buffer)
{
    pid_t pid;
    buffer[strcspn(buffer, "&")] = 0;

    pid = fork();
    if (pid == 0)
    {
        char **args = parse_arguments(buffer);
        execvp(args[0], args);
        _exit(1);
    }

    bg_process_t *proc = malloc(sizeof(bg_process_t));
    proc->pid = pid;
    strncpy(proc->command, buffer, 255);
    proc->next = bg_list;
    bg_list = proc;

    char msg[64];
    snprintf(msg, sizeof(msg), "[%d] %d\n", 1, pid);
    write(STDOUT_FILENO, msg, strlen(msg));
}

void check_background_processes(void)
{
    bg_process_t **curr = &bg_list;
    int status;
    struct rusage usage;

    while (*curr)
    {
        pid_t result = wait4((*curr)->pid, &status, WNOHANG, &usage);
        if (result > 0)
        {
            char msg[256];
            snprintf(msg, sizeof(msg),
                     "[Ended] %s\n", (*curr)->command);
            write(STDOUT_FILENO, msg, strlen(msg));

            bg_process_t *tmp = *curr;
            *curr = (*curr)->next;
            free(tmp);
        }
        else
        {
            curr = &(*curr)->next;
        }
    }
}
