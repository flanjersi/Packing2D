#include <stdio.h>
#include <stdlib.h>

#include "lib/objet.h"
#include "lib/boite.h"
#include "lib/lecture.h"
#include "lib/bande.h"
#include "lib/probleme.h"

int main(void){

	PROBLEME probleme = lecture();

	PROBLEME copy = copie_probleme(probleme);

	print_probleme(probleme);
	print_probleme(copy);
	
	
	return 0;
}


