#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#define max(a,b) (a>=b? a:b)

#include "sac_a_dos.h"


/* Recuper une solution optimal pour une matrice donné en ne prennant pas compte du retournement des objets*/

void takeBestSolution(PROBLEME probleme , BANDE bande, int **matrice, int ligne, int colonne){

	if(ligne > 0 && colonne > 0){
		if((matrice[ligne - 1][colonne] == matrice[ligne][colonne]))
			takeBestSolution(probleme, bande, matrice, ligne - 1, colonne);
		else{
			takeBestSolution(probleme, bande, matrice, ligne - 1, colonne - probleme->objets[ligne-1]->hauteur);
			
			if(canadd_objectInStripe(bande, probleme->objets[ligne-1], probleme->boite->hauteur)){
				ajouterObjetDansBande(bande, probleme->objets[ligne-1], probleme->boite->hauteur);
			}
		}
	}
}

/* Recuper une solution optimal pour une matrice donné en prenant compte du retournement des objets*/

void takeBestSolutionRotate(PROBLEME probleme, BANDE bande, int **matrice, int ligne, int colonne, int *tabRotate){
	if(ligne > 0 && colonne > 0){
		if(matrice[ligne - 1][colonne] == matrice[ligne][colonne])
			takeBestSolutionRotate(probleme, bande, matrice, ligne - 1, colonne, tabRotate);
		
		else if(tabRotate[ligne - 1] == 1){
			takeBestSolutionRotate(probleme, bande, matrice, ligne - 1, colonne - probleme->objets[ligne-1]->largeur, tabRotate);
			
			if(canadd_objectInStripe(bande, probleme->objets[ligne-1], probleme->boite->hauteur))
				ajouterObjetRotateDansBande(bande, probleme->objets[ligne-1]);
		}
		
		else{
			takeBestSolutionRotate(probleme, bande, matrice, ligne - 1, colonne - probleme->objets[ligne-1]->hauteur, tabRotate);
			
			if(canadd_objectInStripe(bande, probleme->objets[ligne-1], probleme->boite->hauteur))
				ajouterObjetDansBandeTest(bande, probleme->objets[ligne-1]);
		
		}
	}

}

/* 
	Remplir une matrice , pour pouvoir construire une solution optimal d'un problème pour une largeur de bande donner
	En tenant compte du retournement des objets
*/

void fillTabRotate(PROBLEME probleme,  int **matrice, int largeur, int *tabRotate){

	for(int hauteur = 0 ; hauteur <= probleme->boite->hauteur ; hauteur++)
		matrice[0][hauteur] = 0;

	for(int objetIndex = 0 ; objetIndex < probleme->nbObjets; objetIndex++){
		for(int hauteur = 0 ; hauteur <= probleme->boite->hauteur ; hauteur++){
			if(probleme->objets[objetIndex]->isInBox) // Si l'objet est déjà dans la boite
				matrice[objetIndex+1][hauteur] = matrice[objetIndex][hauteur];
			//Si l'objet ne rentre pas normalement alors
			else if(probleme->objets[objetIndex]->hauteur > hauteur || probleme->objets[objetIndex]->largeur > largeur){ 
				//On vérifie qu'il rentre si on le retourne
				if(probleme->objets[objetIndex]->largeur <= hauteur && probleme->objets[objetIndex]->hauteur <= largeur){
					int rotate = matrice[objetIndex][hauteur - probleme->objets[objetIndex]->largeur] + 
							(probleme->objets[objetIndex]->hauteur * probleme->objets[objetIndex]->largeur);
					
					matrice[objetIndex+1][hauteur] = max(matrice[objetIndex][hauteur], rotate);
					tabRotate[objetIndex] = 1; 
				}
				//Sinon on ne le prend pas
				else
					matrice[objetIndex+1][hauteur] = matrice[objetIndex][hauteur];
			}
			//Si l'objet rentre normalement alors ..
			else
				matrice[objetIndex+1][hauteur] = max(matrice[objetIndex][hauteur], 
						matrice[objetIndex][hauteur - probleme->objets[objetIndex]->hauteur] + 
							(probleme->objets[objetIndex]->hauteur * probleme->objets[objetIndex]->largeur));
		}
    }
}

/* 
	Remplir une matrice , pour pouvoir construire une solution optimal d'un problème pour une largeur de bande donner
	En ne tenant pas compte du retournement des objets
*/

void fillTab(PROBLEME probleme,  int **matrice, int largeur){

	for(int hauteur = 0 ; hauteur <= probleme->boite->hauteur ; hauteur++)
		matrice[0][hauteur] = 0;

	for(int objetIndex = 0 ; objetIndex < probleme->nbObjets; objetIndex++){
		for(int hauteur = 0 ; hauteur <= probleme->boite->hauteur ; hauteur++){
			if(probleme->objets[objetIndex]->isInBox || probleme->objets[objetIndex]->hauteur > hauteur || probleme->objets[objetIndex]->largeur > largeur)
				matrice[objetIndex+1][hauteur] = matrice[objetIndex][hauteur];
			else
				matrice[objetIndex+1][hauteur] = max(matrice[objetIndex][hauteur], 
						matrice[objetIndex][hauteur - probleme->objets[objetIndex]->hauteur] + 
							(probleme->objets[objetIndex]->hauteur * probleme->objets[objetIndex]->largeur));
		}
    }
}


/* 
	Affichage d'une matrice
*/

void print_matrice(int **matrice, int nbObjets, int hauteurMax){
	for(int objet = 0 ; objet < nbObjets ; objet++){
		for( int hauteur = 0 ; hauteur <= hauteurMax ; hauteur++)
			printf("%3d ", matrice[objet][hauteur]);
		printf("\n");
	}

	printf("\n\n");
}




