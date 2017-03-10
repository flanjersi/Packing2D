#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "boite.h"

/* 
	Creer une boite avec une largeur, unt hauteur, un nombre d'objet maximum et un nombre de bandes initial
*/

BOITE creer_boite(int largeur, int hauteur, int nbObjets, int nbBandes){
	BOITE b = malloc(sizeof(struct Boite));
	assert(b != NULL);
	
	b->largeur = largeur;
	b->hauteur = hauteur;	
	b->surfaceRempli = 0;

	b->nbObjetsInBox = 0;
	b->isInBox = malloc(nbObjets * sizeof(int));
	
	b->nbBandes = nbBandes;
	b->bandes = malloc(nbBandes * sizeof(struct Bande));
	
	for (int numObjet = 0 ; numObjet < nbObjets ; numObjet++){
		b->isInBox[numObjet] = 0;
	}
	
	return b;
}

/* 
	Supprime l'espace mémoire d'une boite donné
*/
void liberer_boite(BOITE boite){
	free(boite->isInBox);

	for(int index = 0 ; index < boite->nbBandes ; index++)	
		liberer_bande(boite->bandes[index]);
	free(boite->bandes);

	free(boite);
}

/* 
	creer une bande avec une largeur, une position X et Y, et un nombre d'objet maximal dans une boite donné , 
*/

void creerEtAjouterBande(BOITE boite, int largeur, int nbObjectsMax, int positionX, int positionY){
	boite->bandes = realloc(boite->bandes, sizeof(struct Bande)*(boite->nbBandes + 1));
	boite->bandes[boite->nbBandes] = creer_bande(largeur, nbObjectsMax, positionX, positionY);
	boite->nbBandes++;
}

/* 
	Vérifie si l'on peux ajouter une bande dans une boite
*/

int canAddStripe(BOITE boite, BANDE bande){
	if(bande->largeur + bande->positionX <= boite->largeur)
		return 1;
	return 0;
}

/* 
	Ajoute une bande dans une boite en effectuant sa copie a la fin du tableau des bandes de notre boite
*/

void addStripe2(BOITE boite, OBJET *listeObjet, BANDE bande, int nbObjectsMax){
	boite->bandes = realloc(boite->bandes, sizeof(struct Bande) * (boite->nbBandes + 1));
	boite->bandes[boite->nbBandes] = copie_bande(bande, nbObjectsMax);
	boite->surfaceRempli += bande->surfaceRempli;

	for( int indexObjet = 0 ; indexObjet < nbObjectsMax ; indexObjet++)
		if(bande->isInStripe[indexObjet] == 1)
			listeObjet[indexObjet]->isInBox = 1;
	
	boite->nbObjetsInBox += bande->nbObjets;
	boite->nbBandes++;
}

/* 
	Ajoute un objet dans une boite, sans passé par une bande. Par son indice on peut acceder a sa "valeur" dans notre liste d'objets.
*/

void addObjet(BOITE boite, OBJET *objets, int indiceObjet){
	boite->surfaceRempli += objets[indiceObjet]->largeur * objets[indiceObjet]->hauteur; 
	boite->nbObjetsInBox++;
	boite->isInBox[indiceObjet] = 1;
	objets[indiceObjet]->isInBox = 1;
}

/* 
	Renvoie 1 si la boite a atteint son nombre d'objet maximum , 0 sinon
*/

int estPleine(BOITE boite, int nbObjets){
	return (nbObjets == boite->nbObjetsInBox);
}


/* 
	Fait la copie d'une boite et la renvoie
*/

BOITE copie_boite(BOITE boite, int nbObjetsMax){
	BOITE copy = creer_boite(boite->largeur, boite->hauteur, nbObjetsMax, boite->nbBandes);
	
	copy->surfaceRempli = boite->surfaceRempli;
	copy->nbObjetsInBox = boite->nbObjetsInBox;

	for(int index = 0 ; index < nbObjetsMax ; index++){
		copy->isInBox[index] = boite->isInBox[index];
	}

	for(int indexBande = 0 ; indexBande < boite->nbBandes ; indexBande++){
		copy->bandes[indexBande] = copie_bande(boite->bandes[indexBande], nbObjetsMax);
	}

	return copy;

}

/* 
	Affiche toutes les bandes d'une boite donnée
*/

void afficher_boiteBande(BOITE boite, OBJET *objets, int nbObjets){
	printf("Boite : nbObjets : %d | hauteur : %d | largeur : %d \n\n", boite->nbObjetsInBox, boite->hauteur, boite->largeur );

	for (int numBande = 0; numBande < boite->nbBandes ; numBande++){
		printf("\t");
		afficher_bande(boite->bandes[numBande], objets, nbObjets);
	}
}

/* 
	Affiche tous les objets d'une boite donné sans afficher les bandes
*/

void afficher_boiteObjet(BOITE boite, OBJET *objets, int nbObjets){
	printf("Boite : nbObjets : %d | hauteur : %d | largeur : %d \n\n", boite->nbObjetsInBox, boite->hauteur, boite->largeur );

	for (int numObjet = 0; numObjet < nbObjets ; numObjet++){
		printf("\t");
		afficher_objet(objets[numObjet]);
	}
}












