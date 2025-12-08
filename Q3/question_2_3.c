#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <stdlib.h>
#include "question_2_3.h"

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

	pid_t pid = fork();
	if (pid == 0) {
		execlp(buffer, buffer, NULL);
		_exit(1);
	} else if (pid > 0) {
		wait(NULL);
	} else {
		write(STDERR_FILENO, ERROR, strlen(ERROR));
	}
}
