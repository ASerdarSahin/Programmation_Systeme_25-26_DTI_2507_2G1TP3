#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <stdlib.h>
#include "question_2_3.h"
#include "question_4_5.h"
#include <errno.h>
#include <signal.h>
#include <time.h>

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
		struct timespec start, end;
		clock_gettime(CLOCK_MONOTONIC, &start);

		int status;
		wait(&status);

		clock_gettime(CLOCK_MONOTONIC, &end);

		long seconds = end.tv_sec - start.tv_sec;
		long nanoseconds = end.tv_nsec - start.tv_nsec;
		last_execution_time_ms = seconds * 1000 + nanoseconds / 1000000;

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
