#ifndef __STRIPE__
#define __STRIPE__

#include "objet.h"


typedef struct Bande *BANDE;

struct Bande{
	int largeur;
	int hauteur;
	
	int positionX;
	int positionY;
	
	int surfaceRempli;
	
	int nbObjets;
	int *isInStripe;
};

BANDE copie_bande(BANDE bande, int nbObjetsMax);
BANDE creer_bande(int largeur, int nbObjectsMax, int positionX, int positionY);
void ajouterObjetDansBande(BANDE s, OBJET o, int hauteurMax);
void ajouterObjetRotateDansBande(BANDE s, OBJET o);
void ajouterObjetDansBandeTest(BANDE s, OBJET o);
int canadd_objectInStripe(BANDE s, OBJET o, int hauteurMax);
void afficher_bande(BANDE bande, OBJET *objets, int nbObjets);
void liberer_bande(BANDE bande);

#endif