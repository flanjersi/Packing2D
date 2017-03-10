#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lib/objet.h"
#include "lib/boite.h"
#include "lib/bande.h"

int main(void){

	char nom[] = "rouge";
	
	OBJET *objets = malloc(sizeof(struct Objet) * 2);

	objets[0] = creer_objet(nom, 10, 10, 0);
	strcpy(nom, "vert");
	objets[1] = creer_objet(nom, 20, 20, 1);


	BANDE bande = creer_bande(10, 2, 0, 0);
	if(canadd_objectInStripe(bande, objets[0], 10))
		ajouterObjetDansBande(bande, objets[0], 10);
	if(canadd_objectInStripe(bande, objets[1], 10))
		ajouterObjetDansBande(bande, objets[1], 10);
		

	afficher_bande(bande, objets, 2);

	liberer_objet(objets[0]);
	liberer_objet(objets[1]);
	free(objets);
	
	liberer_bande(bande);


	return 0;
}


