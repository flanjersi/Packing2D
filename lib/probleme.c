#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "probleme.h"

/* 
	Creation d'un problème vide
*/

PROBLEME cree_probleme(int nbObjets, int hauteur, int largeur){
	PROBLEME probleme = malloc(sizeof(struct Probleme));
	assert(probleme != NULL);

	probleme->boite = creer_boite(largeur, hauteur, nbObjets, 0);
	probleme->objets = malloc(sizeof(struct Objet) * nbObjets);
	assert(probleme->objets != NULL);

	probleme->nbObjets = nbObjets;


	return probleme;
}

/* 
	Copie d'un problème
	On retourne la copie d'un problème donné
*/

PROBLEME copie_probleme(PROBLEME probleme){
	PROBLEME copy = cree_probleme(probleme->nbObjets, probleme->boite->hauteur, probleme->boite->largeur);
	
	copy->boite = copie_boite(probleme->boite, probleme->nbObjets);
	copy->objets = copie_listObjet(probleme->objets, probleme->nbObjets);

	return copy;
}



/* 
	Libération de la mémoire d'un problème alloué
*/

void liberer_probleme(PROBLEME probleme){
	liberer_boite(probleme->boite);

	for(int indexObjet = 0 ; indexObjet < probleme->nbObjets ; indexObjet++)
		liberer_objet(probleme->objets[indexObjet]);

	free(probleme->objets);

	free(probleme);
}


/* -------------------- Partie afffichage ----------------------------*/

/* Affichage de la boite d'un problème avec tous les objets*/

void print_helpProbleme(PROBLEME probleme){
	afficher_boiteObjet(probleme->boite, probleme->objets, probleme->nbObjets);
}

/* Affichage du problème de façon similaire à la première fonction*/

void print_probleme(PROBLEME probleme){
	printf("%d %d\n", probleme->boite->largeur, probleme->boite->hauteur);
	printf("%d\n", probleme->nbObjets);
	
	for(int index_objet = 0 ; index_objet < probleme->nbObjets ; index_objet++){
			printf("%s %d %d \n", probleme->objets[index_objet]->nom, probleme->objets[index_objet]->largeur, probleme->objets[index_objet]->hauteur);
	}

}

/* Affichage du problème en affichant toutes les bandes de la boite de celui-ci*/

void print_problemeBANDE(PROBLEME probleme){

	afficher_boiteBande(probleme->boite, probleme->objets, probleme->nbObjets);

	printf("\n\n");
}

/*
	Test de la possibilité de rupture entre deux problèmes donné
	Nous considérant dans ce cas, la différence d'espace perdu

*/

int test_rupture(PROBLEME remplissageCourrant, PROBLEME bestRemplissage){
	if(bestRemplissage->boite->surfaceRempli == bestRemplissage->boite->hauteur * bestRemplissage->boite->largeur)
		return 1;

	int lastBande_best = 0, lastBande_courrant = 0;
	int longueur_rempliBest = 0, longueur_remplicourrant = 0;
	int espacePerdu_remplissageCourrant = 0, espacePerdu_remplissageBest = 0;
	int surface_maxCourrant  = 0,surface_maxBest = 0;

	/*
		Si le remplissage courant possède au moins une bande, alors on accède à la derniere pour
		calculer la longueur déjà rempli de la boite
	*/

	if(remplissageCourrant->boite->nbBandes > 0){
		lastBande_courrant = remplissageCourrant->boite->nbBandes - 1;
		longueur_remplicourrant = remplissageCourrant->boite->bandes[lastBande_courrant]->positionX
								 + remplissageCourrant->boite->bandes[lastBande_courrant]->largeur;

	}

	/* De même mais pour l'autre */

	if(bestRemplissage->boite->nbBandes > 0){
		lastBande_best = bestRemplissage->boite->nbBandes - 1;
		longueur_rempliBest = bestRemplissage->boite->bandes[lastBande_best]->positionX
								 + bestRemplissage->boite->bandes[lastBande_best]->largeur;
	}
	
	surface_maxCourrant = longueur_remplicourrant * remplissageCourrant->boite->hauteur;
	espacePerdu_remplissageCourrant = surface_maxCourrant - remplissageCourrant->boite->surfaceRempli;
	
	
	surface_maxBest = longueur_rempliBest * bestRemplissage->boite->hauteur;
	espacePerdu_remplissageBest = surface_maxBest - bestRemplissage->boite->surfaceRempli;
	
	return espacePerdu_remplissageBest < espacePerdu_remplissageCourrant;
}

/* ---------------------------- Partie affichage des solutions du problème---------------------------------*/




/*
void print_solution(PROBLEME probleme){
	printf("%d %d\n", probleme->boite->largeur, probleme->boite->hauteur);
	printf("%d\n", probleme->nbObjets);
	
	for(int index_objet = 0 ; index_objet < probleme->nbObjets ; index_objet++){	
			printf("%d %s %d %d %d %d %d\n", probleme->objets[index_objet]->indice, probleme->objets[index_objet]->nom, probleme->objets[index_objet]->largeur, probleme->objets[index_objet]->hauteur, 
					probleme->objets[index_objet]->positionX, probleme->objets[index_objet]->positionY, probleme->objets[index_objet]->isRotate);
	}
}
*/

void print_solution(PROBLEME probleme){
	printf("%d %d\n", probleme->boite->largeur, probleme->boite->hauteur);
	printf("%d\n", probleme->nbObjets);
	int* tab_ObjetPasRentre = malloc(sizeof(int) * probleme->nbObjets);
	int* tab_ObjetRentre = malloc(sizeof(int) * probleme->nbObjets);
	
	for(int i = 0 ; i < probleme->nbObjets ; i++){
		tab_ObjetRentre[i] = 0;
		tab_ObjetPasRentre[i] = 0;
	}


	for(int index_bande = 0 ; index_bande < probleme->boite->nbBandes ; index_bande++){	
		for(int index_objet = 0 ; index_objet < probleme->nbObjets ; index_objet++){
			if(probleme->boite->bandes[index_bande]->isInStripe[index_objet] == 1){
				printf("%d %s %d %d %d %d %d\n", probleme->objets[index_objet]->indice, 
					probleme->objets[index_objet]->nom, 
					probleme->objets[index_objet]->largeur, probleme->objets[index_objet]->hauteur, 
					probleme->objets[index_objet]->positionX, probleme->objets[index_objet]->positionY, 
					probleme->objets[index_objet]->isRotate);
				tab_ObjetRentre[index_objet] = 1;
			}
		}
	}
	
	for(int index_objet = 0 ; index_objet < probleme->nbObjets ; index_objet++){
		if(!tab_ObjetRentre[index_objet]){
			printf("%d %s %d %d %d %d %d\n", probleme->objets[index_objet]->indice, 
					probleme->objets[index_objet]->nom, 
					probleme->objets[index_objet]->largeur, probleme->objets[index_objet]->hauteur, 
					-1, -1, 
					probleme->objets[index_objet]->isRotate);
			
		}
	}
}








