#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <stdlib.h>
#include "question_2_3.h"
#include "question_4.h"
#include <errno.h>
#include <signal.h>
//look up the w macros

void execute_one_simple_command(){
	char buffer[MAX_LINE_SIZE]={0};
	int nb_char_read=read(STDIN_FILENO, buffer, MAX_LINE_SIZE);

	if (nb_char_read == 0) {
		write(STDOUT_FILENO, BYE, strlen(BYE));
		exit(0);
	}

	buffer[nb_char_read-1]=0;

	if (strcmp(buffer, "exit") == 0) {
		write(STDOUT_FILENO, BYE, strlen(BYE));
		exit(0);
	}

	char *args[MAX_LINE_SIZE];
	int i = 0;
	char *token = strtok(buffer, " \t");
	while (token != NULL && i < MAX_LINE_SIZE - 1) {
	  args[i++] = token;
	  token = strtok(NULL, " \t");
	}
	args[i] = NULL;
	if (args[0] == NULL) return;

	signal(SIGINT, SIG_IGN);

	pid_t pid = fork();
	if (pid == 0) {
		signal(SIGINT, SIG_DFL);
		execvp(args[0], args);
		_exit(1);
	} else if (pid > 0) {
		int status;
		wait(&status);

		signal(SIGINT, SIG_DFL);

		if(WIFEXITED(status)) {
		  last_exit_code = WEXITSTATUS(status);
		  last_signal = -1;
		}
		else if (WIFSIGNALED(status)) {
		  last_signal = WTERMSIG(status);
		  last_exit_code = -1;
		}
	} else {
		write(STDERR_FILENO, ERROR, strlen(ERROR));
	}
}
