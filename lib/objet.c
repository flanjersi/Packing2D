#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "objet.h"



/* 
	creer un objet suivant un nom, une largeur, une hauteur et un indice.
	Initialise ses champs et renvoie l'objet creer
*/

OBJET creer_objet(char nom[], int largeur, int hauteur, int indice){
	OBJET o = malloc(sizeof(struct Objet));
	assert(o != NULL);

	o->nom = malloc(sizeof(char) * (strlen(nom) + 1));
	strcpy(o->nom, nom);
	
	o->indice = indice;
	
	o->largeur = largeur;
	o->hauteur = hauteur;
	
	o->isRotate = 0;
	
	o->positionX = -1;
	o->positionY = -1;
	
	o->isInBox = 0;
	
	return o;
}



/* 
	creer un objet suivant un nom, une largeur, une hauteur, des postion X et Y et un booleen pour savoir si il est retourner
	et enfin son indice.
	Initialise ses champs et renvoie l'objet creer
*/

OBJET creer_objetPosition(char nom[], int largeur, int hauteur, int indice, int rotation, int positionX, int positionY){
	OBJET o = malloc(sizeof(struct Objet));
	assert(o != NULL);

	o->nom = malloc(sizeof(char) * (strlen(nom) + 1));
	strcpy(o->nom, nom);
	
	o->indice = indice;
	
	o->largeur = largeur;
	o->hauteur = hauteur;
	
	o->isRotate = rotation;
	
	o->positionX = positionX;
	o->positionY = positionY;
	
	o->isInBox = 0;
	
	return o;
}

/* 
	copie un objet et renvoie la copie
*/

OBJET copie_objet(OBJET objet){
	OBJET copy = creer_objetPosition(objet->nom, objet->largeur, objet->hauteur, objet->indice, objet->isRotate, objet->positionX, objet->positionY);
	
	copy->isInBox = objet->isInBox;

	return copy;
}


/* 
	copie une liste d'objet et renvoie sa copie
*/

OBJET* copie_listObjet(OBJET* objets, int nbObjets){
	OBJET* copy = malloc(sizeof(struct Objet) * nbObjets);

	for(int indexObjet = 0 ; indexObjet < nbObjets ; indexObjet++)
		copy[indexObjet] = copie_objet(objets[indexObjet]);

	return copy;
}

/* 
	Libere l'espace alloué d'un objet donné
*/

void liberer_objet(OBJET objet){
	free(objet->nom);
	free(objet);
}


/* 
	Affiche un objet donné
*/
void afficher_objet(OBJET objet){
	printf("- indice : %d | nom : %s, largeur : %d, hauteur : %d, Rotation : %d, positionX : %d, positionY : %d\n", objet->indice, objet->nom,
		objet->largeur, objet->hauteur, 
		objet->isRotate, 
		objet->positionX, objet->positionY );
}
