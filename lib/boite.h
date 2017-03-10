#ifndef __BOX__
#define __BOX__


#include "objet.h"
#include "bande.h"


typedef struct Boite *BOITE;
struct Boite{
	int largeur;
	int hauteur;
	
	int *isInBox;
	int nbObjetsInBox;

	BANDE *bandes;
	int nbBandes;
	
	int surfaceRempli;
	
};


BOITE copie_boite(BOITE boite, int nbObjetsMax);
BOITE creer_boite(int largeur, int hauteur, int nbObjets, int nbBandes);
void liberer_boite(BOITE boite);
void creerEtAjouterBande(BOITE boite, int largeur, int nbObjectsMax, int positionX, int positionY);
int canAddStripe(BOITE boite, BANDE bande);
void addStripe2(BOITE boite, OBJET *listeObjet, BANDE bande, int nbObjectsMax);
void addObjet(BOITE boite, OBJET *objets, int indiceObjet);
int estPleine(BOITE boite, int nbObjets);
void afficher_boiteBande(BOITE boite, OBJET *objets, int nbObjets);
void afficher_boiteObjet(BOITE boite, OBJET *objets, int nbObjets);
/*int* initTabIndexForSAD(BOITE box);*/


#endif