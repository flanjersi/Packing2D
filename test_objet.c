#include <stdio.h>
#include <stdlib.h>
#include "lib/objet.h"



int main(void){

	char nom[] = "rouge";
	OBJET o = creer_objet(nom, 10, 10, 0);

	afficher_objet(o);

	liberer_objet(o);
	return 0;
}