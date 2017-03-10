#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "lecture.h"

/* 
	Lis le contenu du probleme d'un fichier sur l'entrée standard
	et le renvoie dans une structure probleme
*/

PROBLEME lecture(){

	char nom[10];
	int hauteur, largeur, nbObjets, cptObjet = 0;

	scanf("%d %d", &largeur, &hauteur);
	scanf("%d", &nbObjets);
	PROBLEME probleme = cree_probleme(nbObjets, hauteur, largeur);
	
	while(scanf("%s %d %d", nom, &largeur, &hauteur) == 3){
		probleme->objets[cptObjet] = creer_objet(nom, largeur, hauteur, cptObjet);
		cptObjet++;
	}

	
	return probleme;
}

/* 
	Lis le contenu d'une solution d'un fichier sur l'entrée standard
	et le renvoie dans une structure probleme
*/


PROBLEME lectureSolution(){

	char nom[10];
	int hauteur, largeur, nbObjets, positionX, positionY, rotation, cptObjet = 0, indice;

	scanf("%d %d", &hauteur, &largeur);
	scanf("%d", &nbObjets);

	PROBLEME probleme = cree_probleme(nbObjets, hauteur, largeur);
	
	while(scanf("%d %s %d %d %d %d %d", &indice, nom, &largeur, &hauteur, &positionX, &positionY, &rotation) == 7){
		probleme->objets[cptObjet] = creer_objetPosition(nom, largeur, hauteur, indice, rotation, positionX, positionY);
		cptObjet++;
	}

	
	return probleme;
}
