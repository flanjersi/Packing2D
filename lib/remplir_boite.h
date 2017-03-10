#ifndef __REMPLIRBOITE__
#define __REMPLIRBOITE__

#include "objet.h"
#include "bande.h"
#include "boite.h"
#include "probleme.h"
#include "k_largeurs_valides.h"
#include "sac_a_dos.h"

PROBLEME bestRemplissage;

void remplir_boite(int longueur, int k, PROBLEME remplissageCourrant, int profondeur);
BANDE remplir_bandeSAD(int largeur, PROBLEME probleme);

void remplir_boiteGlouton(int longueur, int hauteurBoite, int k, PROBLEME remplissageCourrant);
BANDE remplir_bandeGlouton(int largeur, PROBLEME probleme);

#endif