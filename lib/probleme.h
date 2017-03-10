#ifndef __PROBLEME__
#define __PROBLEME__


#include "objet.h"
#include "bande.h"
#include "boite.h"

typedef struct Probleme *PROBLEME;
struct Probleme{
	BOITE boite;

	int nbObjets;
	OBJET *objets;
};

PROBLEME copie_probleme(PROBLEME probleme);
PROBLEME cree_probleme(int nbObjets, int hauteur, int largeur);
void liberer_probleme(PROBLEME probleme);
void print_solution(PROBLEME probleme);
void print_probleme(PROBLEME probleme);
void print_helpProbleme(PROBLEME probleme);
void print_problemeBANDE(PROBLEME probleme);
int test_rupture(PROBLEME remplissageCourrant, PROBLEME bestRemplissage);

#endif