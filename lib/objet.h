#ifndef __OBJECT__
#define __OBJECT__

#define NONE (-1)


typedef struct Objet *OBJET;

struct Objet{
	char *nom;
	int indice;
	int largeur;
	int hauteur;
	int positionX;
	int positionY;
	int isRotate;

	int isInBox;
};

OBJET creer_objet(char nom[], int largeur, int hauteur, int indice);
OBJET creer_objetPosition(char nom[], int largeur, int hauteur, int indice, int rotation, int positionX, int positionY);
void liberer_objet(OBJET objet);
void afficher_objet(OBJET objet);
OBJET* copie_listObjet(OBJET* objets, int nbObjets);
OBJET copie_objet(OBJET objet);


#endif