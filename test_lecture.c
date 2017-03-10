#include <stdio.h>
#include <stdlib.h>

#include "lib/lecture.h"
#include "lib/probleme.h"

int main(void){

	PROBLEME probleme = lecture();
	
	print_probleme(probleme);

	return 0;
}


