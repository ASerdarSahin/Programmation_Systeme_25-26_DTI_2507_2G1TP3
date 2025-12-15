#include <unistd.h>
#include <string.h>
#include "question_1.h"
#include "question_4.h"
#include <stdio.h>
void display_welcome_prompt(){
	write(STDOUT_FILENO, WELCOME_PROMPT, strlen(WELCOME_PROMPT));
}

void display_regular_prompt(){
	char prompt[PROMPT_BUFFER_SIZE];
	int len;

	if (last_signal != -1) {
	  len = snprintf(prompt, PROMPT_BUFFER_SIZE,
			"Enseash [sign:%d] %%\n", last_signal);
	}
	else if (last_exit_code != -1) {
	  len = snprintf(prompt, PROMPT_BUFFER_SIZE,
			"Enseash [exit:%d] %%\n", last_exit_code);
	}
	else {
	  len = snprintf(prompt, PROMPT_BUFFER_SIZE,
			"Enseash %%\n");
	}

	write(STDOUT_FILENO, prompt, len);
}
