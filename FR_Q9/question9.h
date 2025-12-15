#ifndef QUESTION9_H
#define QUESTION9_H

#include <sys/types.h>

typedef struct bg_process
{
    pid_t pid;
    char command[256];
    struct bg_process *next;
} bg_process_t;

void launch_background(char *buffer);
void check_background_processes(void);

#endif
