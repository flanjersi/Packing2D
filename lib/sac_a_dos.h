#ifndef __SAC_A_DOS__
#define __SAC_A_DOS__ 

#include "boite.h"
#include "bande.h"
#include "objet.h"
#include "probleme.h"
#include "k_largeurs_valides.h"



void fillTab(PROBLEME probleme,  int **matrice, int largeur);
void fillTabRotate(PROBLEME probleme,  int **matrice, int largeur, int *tabRotate);
void print_matrice(int **matrice, int nbObjects, int hauteurMax);
void takeBestSolution(PROBLEME probleme , BANDE bande, int **matrice, int ligne, int colonne);
void takeBestSolutionRotate(PROBLEME probleme, BANDE bande, int **matrice, int ligne, int colonne, int *tabRotate);


#endif
