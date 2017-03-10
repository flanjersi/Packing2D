#include <stdio.h>
#include <stdlib.h>

#include "tri.h"

/* 
	Permuter deux objets
*/

void Permuter(int *tabScore, int* tabIndiceObjet, int k, int p){
	int temp = tabScore[k];
	tabScore[k] = tabScore[p];
	tabScore[p] = temp;

	temp = tabIndiceObjet[k];
	tabIndiceObjet[k] = tabIndiceObjet[p];
	tabIndiceObjet[p] = temp;
}

/* 
	Affichage d'une série donné d'une taille donner
*/

void PrintSerie(int *s, int n){
	int i;
	
	for(i = 0 ; i < n ; i++)
		printf("%d ", s[i]);
	printf("\n");
}

/* 
	Tri d'un tableau, et tri du tableau des indices par rapport au tri du premier
*/

void Quick_Sort(int* tabScore, int* tabIndiceObjet, int gauche, int droite) {

	int milieu;
	int a = gauche, b = droite;
	if(droite > gauche) {
		milieu = tabScore[(gauche+droite)/2];
		while (a <= b) {
			while (tabScore[a] > milieu) a++;
			while (tabScore[b] < milieu) b--;
			if (a <= b) {
				Permuter (tabScore, tabIndiceObjet, a, b);
				a++; b--;
			}
		}
		Quick_Sort (tabScore, tabIndiceObjet, gauche, b);
		Quick_Sort (tabScore, tabIndiceObjet, a, droite);
	}
}