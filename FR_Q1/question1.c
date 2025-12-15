#include <unistd.h>
#include <string.h>
#include "question1.h"


void display_welcome_prompt(){
	write(STDOUT_FILENO, WELCOME_PROMPT,strlen(WELCOME_PROMPT));
}

void print_prompt(void)
{
    const char *prompt = "enseash % ";
    write(STDOUT_FILENO, prompt, strlen(prompt));
}
