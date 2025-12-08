#include <stdio.h>
#include "question_1.h"
#include "question_2_3.h"

int main(){
	display_welcome_prompt();
	while(1){
		display_regular_prompt();
		execute_one_simple_command();
	}
	return 0;
}
