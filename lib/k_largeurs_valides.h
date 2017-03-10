#ifndef __KLARGEUR__
#define __KLARGEUR__

#include "objet.h"
#include "bande.h"
#include "boite.h"
#include "probleme.h"
#include "tri.h"


int selectionner_k_largeurs_valides(int *tab, int longueur, PROBLEME probleme, int k);
int selectionner_k_largeurs_valides_optimiser(int *tab, int longueur, PROBLEME probleme , int k, double delta);
int* occurence_largeur_objets(OBJET* listObjets, int nbObjets, int largeurMax);
int* make_score(OBJET* listObjets, int nbObjets, double delta, int largeurMax);


#endif