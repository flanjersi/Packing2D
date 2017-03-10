#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "remplir_boite.h"

/*

	SAC A DOS

*/


void remplir_boite(int longueur, int k, PROBLEME remplissageCourrant, int profondeur){
	
	if(longueur >= 0){
		int cptLargeur = 0;
		int e = -1;	
		


		if(remplissageCourrant->boite->surfaceRempli > bestRemplissage->boite->surfaceRempli){
			bestRemplissage = copie_probleme(remplissageCourrant);
		}
	
		if(test_rupture(remplissageCourrant, bestRemplissage)){
			return;
		}
		
		int *tab = malloc(sizeof(int) * k);
	 	int tailleTab = selectionner_k_largeurs_valides_optimiser(tab, longueur, remplissageCourrant , k, 0.3);
		//int tailleTab = selectionner_k_largeurs_valides(tab, longueur, remplissageCourrant, k);
		
		if(tailleTab > 0){
			while(cptLargeur < tailleTab){
				e = tab[cptLargeur];
				
				BANDE bande = remplir_bandeSAD(e, remplissageCourrant);
				
				if(canAddStripe(remplissageCourrant->boite, bande) && bande->nbObjets != 0){
					addStripe2(remplissageCourrant->boite, remplissageCourrant->objets, bande, remplissageCourrant->nbObjets);
					//afficher_bande(bande, remplissageCourrant->objets, remplissageCourrant->nbObjets);
				}

				liberer_bande(bande);
				
				cptLargeur++;
				
	
				remplir_boite(longueur - e, k, copie_probleme(remplissageCourrant), profondeur + 1);
				
			}
		}
		free(tab);
		liberer_probleme(remplissageCourrant);
	}


}

/* Remplissage de la bande avec l'algorithme du sac-à-dos */

BANDE remplir_bandeSAD(int largeur, PROBLEME probleme){
	int **matrice = malloc(sizeof(int*) * (probleme->nbObjets+1));
	
	for(int i = 0 ; i <= probleme->nbObjets ; i++)
		matrice[i] = malloc(sizeof(int) * (probleme->boite->hauteur + 1));


	int *tabRotate = malloc(sizeof(int) * probleme->nbObjets);
	
	for(int index = 0 ; index < probleme->nbObjets ; index++)
		tabRotate[index] = 0 ;

	//fillTab(probleme,  matrice, largeur);
	fillTabRotate(probleme,  matrice, largeur, tabRotate);
	int positionX = 0;

	if(probleme->boite->nbBandes != 0) 
		positionX = probleme->boite->bandes[probleme->boite->nbBandes - 1]->positionX + probleme->boite->bandes[probleme->boite->nbBandes - 1]->largeur;

	BANDE solution = creer_bande(largeur, probleme->nbObjets, positionX, 0);
	takeBestSolutionRotate(probleme , solution, matrice, probleme->nbObjets , probleme->boite->hauteur, tabRotate);
	//takeBestSolution(probleme , solution, matrice, probleme->nbObjets , probleme->boite->hauteur);
	


	for(int i = 0 ; i < probleme->nbObjets ; i++)
		free(matrice[i]);
	free(matrice);

	free(tabRotate);
	return solution;
}

/*


	GLOUTON


*/


BANDE remplir_bandeGlouton(int largeur, PROBLEME probleme){
	int positionX = 0;

	if(probleme->boite->nbBandes != 0) 
		positionX =  probleme->boite->bandes[probleme->boite->nbBandes - 1]->positionX + probleme->boite->bandes[probleme->boite->nbBandes - 1]->largeur;

	BANDE solution = creer_bande(largeur, probleme->nbObjets, positionX, 0);
	
	for(int index = 0 ; index < probleme->nbObjets ; index++){
		if(!probleme->objets[index]->isInBox && canadd_objectInStripe(solution, probleme->objets[index], probleme->boite->hauteur)){
			ajouterObjetDansBande(solution, probleme->objets[index], probleme->boite->hauteur);
		}
	}
	
	
	return solution;
}


void remplir_boiteGlouton(int longueur, int hauteurBoite, int k, PROBLEME remplissageCourrant){
	if(longueur >= 0){
		int cptLargeur = 0;	
		int e;

		if(remplissageCourrant->boite->surfaceRempli > bestRemplissage->boite->surfaceRempli){
			bestRemplissage = copie_probleme(remplissageCourrant);
			//print_problemeBANDE(bestRemplissage);
		}
		
		if(test_rupture(remplissageCourrant, bestRemplissage)){
			return;
		}
		

		int *tab = malloc(sizeof(int) * k);
		
		//int tailleTab = selectionner_k_largeurs_valides(tab, longueur, remplissageCourrant, k);
		int tailleTab = selectionner_k_largeurs_valides_optimiser(tab, longueur, remplissageCourrant , k, 0.3);
	
		if(tailleTab > 0){
			while(cptLargeur < tailleTab){
				e = tab[cptLargeur];
				BANDE s = remplir_bandeGlouton(e, remplissageCourrant);
				
				if(canAddStripe(remplissageCourrant->boite, s) && s->nbObjets != 0){
					addStripe2(remplissageCourrant->boite, remplissageCourrant->objets, s, remplissageCourrant->nbObjets);
					//afficher_bande(s, remplissageCourrant->objets, remplissageCourrant->nbObjets);
				}
				
				cptLargeur++;

				remplir_boiteGlouton(longueur - e, hauteurBoite, k, copie_probleme(remplissageCourrant));
			}
		}
		free(tab);
		liberer_probleme(remplissageCourrant);
	}
}




