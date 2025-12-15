#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <stdio.h>

#include "question1.h"
#include "question2.h"
#include "question3.h"
#include "question4.h"
#include "question5.h"
#include "question6.h"
#include "question7.h"
#include "question8.h"
#include "question9.h"

#define BUFSIZE 1024

int main(void)
{
    char buffer[BUFSIZE];
    ssize_t size;

    display_welcome_prompt();

    while (1)
    {
	check_background_processes();
        print_prompt();
        size = read_command(buffer, BUFSIZE);
        if (size == 0)
            break;
       
	if (size == 0 || is_exit_command(buffer))
	{
		write(1, "Bye bye...\n", 11);
		break;
	}
	if (strchr(buffer, '|'))
	{
		execute_pipe(buffer);
		continue;
	}
	if(strchr(buffer, '&'))
	{
		launch_background(buffer);
		continue;
	}
	execute_simple_command(buffer);

    }
    return 0;
}
