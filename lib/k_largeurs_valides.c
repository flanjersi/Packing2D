#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "k_largeurs_valides.h"

int selectionner_k_largeurs_valides(int *tab, int longueur, PROBLEME probleme , int k){
	int cpt = 0;
	int objet_index = 0;
	
	while(cpt < k && objet_index < probleme->nbObjets ){
		if(!probleme->objets[objet_index]->isInBox)
			if (probleme->objets[objet_index]->largeur <= longueur){
				tab[cpt] = probleme->objets[objet_index]->largeur;
				cpt++;
			}
		objet_index++;
	}
	return cpt;
}



int selectionner_k_largeurs_valides_optimiser(int *tab, int longueur, PROBLEME probleme , int k, double delta){
	int* tabScore = make_score(probleme->objets, probleme->nbObjets, delta, longueur);
	
	
	int* tabIndiceObjet = malloc(sizeof(int) * probleme->nbObjets);

	for(int i = 0 ; i < probleme->nbObjets ; i++)
		tabIndiceObjet[i] = i;

	Quick_Sort(tabScore, tabIndiceObjet, 0, probleme->nbObjets - 1);

	int objet_index = 0;
	int cpt = 0;

	while(cpt < k && objet_index < probleme->nbObjets ){
		int indice = tabIndiceObjet[objet_index];

		if(!probleme->objets[indice]->isInBox)
			if (probleme->objets[objet_index]->largeur <= longueur){
				tab[cpt] = probleme->objets[indice]->largeur;
				cpt++;
			}

		objet_index++;
	}

	free(tabScore);
	free(tabIndiceObjet);
	return cpt;

	
}

int* occurence_largeur_objets(OBJET* listObjets, int nbObjets, int largeurMax){
	int* tabOccurence = malloc(sizeof(int) * (largeurMax + 1));
	

	for(int i = 0 ; i <= largeurMax ; i++)
		tabOccurence[i] = 0;


	for(int indexObjet = 0 ; indexObjet < nbObjets ; indexObjet++){
		if(!listObjets[indexObjet]->isInBox && listObjets[indexObjet]->largeur <= largeurMax){
			tabOccurence[listObjets[indexObjet]->largeur]++;
		}
	}
	
	return tabOccurence;
}

int* make_score(OBJET* listObjets, int nbObjets, double delta, int largeurMax){
	int* tabScore = malloc(sizeof(int) * nbObjets);
	int* tabOccurence = occurence_largeur_objets(listObjets, nbObjets, largeurMax);
	
	for(int i = 0 ; i < nbObjets ; i++)
		tabScore[i] = 0;


	for(int indexObjet = 0 ; indexObjet < nbObjets ; indexObjet++){
		if(!listObjets[indexObjet]->isInBox && listObjets[indexObjet]->largeur <= largeurMax){
			double calculLargeur_avecDelta = delta * listObjets[indexObjet]->largeur;
			int calculDeltaLargeur = listObjets[indexObjet]->largeur - (int)calculLargeur_avecDelta;
				
			for(int indexLargeur = listObjets[indexObjet]->largeur ; indexLargeur >= calculDeltaLargeur; indexLargeur--){
				tabScore[indexObjet] += tabOccurence[indexLargeur];
			}
		}
	}
	free(tabOccurence);
	return tabScore;
}
