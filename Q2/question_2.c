#include <unistd.h>
#include "question_2.h"

void execute_one_simple_command(){
	char buffer[MAX_LINE_SIZE]={0};
	int nb_char_read=read(STDIN_FILENO, buffer, MAX_LINE_SIZE);
	buffer[nb_char_read-1]=0;
	execlp(buffer, buffer, NULL);
}
