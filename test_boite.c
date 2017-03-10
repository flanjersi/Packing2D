#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lib/objet.h"
#include "lib/boite.h"
#include "lib/bande.h"

int main(void){

	char nom[] = "rouge";
	
	BOITE boite = creer_boite(10, 10, 2, 0);
	OBJET *objets = malloc(sizeof(struct Objet) * 2);

	objets[0] = creer_objet(nom, 10, 10, 0);
	strcpy(nom, "vert");
	objets[1] = creer_objet(nom, 20, 20, 1);




	addObjet(boite, objets, 0);
	addObjet(boite, objets, 1);


	creerEtAjouterBande(boite, 5, 10, 0, 0);
	creerEtAjouterBande(boite, 5, 10, 5, 0);

	afficher_boiteBande(boite, objets, 2);	
	afficher_boiteObjet(boite, objets, 2);


	liberer_objet(objets[0]);
	liberer_objet(objets[1]);
	free(objets);

	
	liberer_boite(boite);

	return 0;
}


