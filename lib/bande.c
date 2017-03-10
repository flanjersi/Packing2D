#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "bande.h"


/* 
	Creer une bande avec une largeur , un nombre d'objet maximum ( celui de notre liste d'objet),
	une position en x et en y 
*/
BANDE creer_bande(int largeur, int nbObjectsMax, int positionX, int positionY){
	BANDE s = malloc(sizeof(struct Bande));
	assert(s != NULL);
	
	s->isInStripe = malloc(sizeof(int) * nbObjectsMax);
	
	assert(s->isInStripe != NULL);
	for(int objectIndex = 0 ; objectIndex < nbObjectsMax ; objectIndex++){
		s->isInStripe[objectIndex] = 0;
 	}


	s->nbObjets = 0;
	s->largeur = largeur;
	s->hauteur = 0;
	s->positionX = positionX;
	s->positionY = positionY;
	s->surfaceRempli = 0;

	
	
	return s;
}

/* 
	libere l'espace mémoire occupé par une bande
*/

void liberer_bande(BANDE bande){
	free(bande->isInStripe);
	free(bande);
}

/* 
	booleen pour savoir si on peux ou pas ajouter un objet dans une bande, 
	si on peux retourne 1, sinon 0.
	l'hauteur maximum est celle de la boite
*/

int canadd_objectInStripe(BANDE s, OBJET o, int hauteurMax){
	if(!o->isInBox)
		return (((s->hauteur + o->hauteur <= hauteurMax) && (o->largeur <= s->largeur)) || 
				((s->hauteur + o->largeur <= hauteurMax) && (o->hauteur <= s->largeur)));
	return 0;

}

/* 
	ajoute un objet dans une bande tel que si l'objet ne rentre pas en largeur il le retourne
	et l'ajoute par rapport a sa hauteur, et le définit retourné dans ses champs respectifs
*/

void ajouterObjetDansBande(BANDE s, OBJET o, int hauteurMax){
	s->isInStripe[o->indice] = 1;
	
	o->positionY = s->hauteur;
	
	s->surfaceRempli += o->hauteur * o->largeur;

	if(s->hauteur + o->hauteur <= hauteurMax && o->largeur <= s->largeur)
	 	s->hauteur += o->hauteur;
	else{
	 	s->hauteur += o->largeur;
	 	o->isRotate = 1;
	}
	
	o->positionX = s->positionX;
	s->nbObjets++;
}

/* 
	ajoute un oobjet dans une bande uniquement en fonction de sa largeur, attention a son utilisation
*/
void ajouterObjetDansBandeTest(BANDE s, OBJET o){


	s->isInStripe[o->indice] = 1;
	
	o->positionY = s->hauteur;
	
	s->surfaceRempli += o->hauteur * o->largeur;

	s->hauteur += o->hauteur;
	
	o->positionX = s->positionX;

	s->nbObjets++;

	//if(s->positionX == 272)
	//	printf("%d\n",s->hauteur);
}



/* 
	La meme chose mais pour un objet retourné
*/

void ajouterObjetRotateDansBande(BANDE s, OBJET o){
	s->isInStripe[o->indice] = 1;
	
	o->positionY = s->hauteur;
	
	s->surfaceRempli += o->hauteur * o->largeur;

	s->hauteur += o->largeur;
	
	o->isRotate = 1;
	
	o->positionX = s->positionX;
	s->nbObjets++;
}


/* 
	copie et retourne la copie de la bande
*/
BANDE copie_bande(BANDE bande, int nbObjetsMax){
	BANDE copie = creer_bande(bande->largeur, nbObjetsMax, bande->positionX, bande->positionY);

	copie->surfaceRempli = bande->surfaceRempli;
	copie->hauteur = bande->hauteur;
	copie->nbObjets = bande->nbObjets;

	for(int index = 0 ; index < nbObjetsMax ; index++){
		copie->isInStripe[index] = bande->isInStripe[index];
	}

	return copie;
}


/* 
	Affiche une bande suivant les objets quelle contient	
*/
void afficher_bande(BANDE bande, OBJET *objets, int nbObjets){
	printf("BANDE : nbObject : %d, hauteur : %d, largeur : %d, positionX : %d, positionY: %d \n", bande->nbObjets, 
																									bande->hauteur, bande->largeur, 
																									bande->positionX, bande->positionY);

	for (int numObjet = 0; numObjet < nbObjets ; numObjet++){
		if(bande->isInStripe[numObjet]){
			printf("\t\t");
			afficher_objet(objets[numObjet]);
		}
	}
}



