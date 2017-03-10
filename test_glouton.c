#include <stdio.h>
#include <stdlib.h>

#include "lib/objet.h"
#include "lib/boite.h"
#include "lib/lecture.h"
#include "lib/remplir_boite.h"
#include "lib/bande.h"
#include "lib/probleme.h"


int main(void){

	PROBLEME probleme = lecture();
	
	bestRemplissage = cree_probleme(0,
									probleme->boite->hauteur, 
									probleme->boite->largeur);

	
	remplir_boiteGlouton(probleme->boite->largeur, probleme->boite->hauteur, 2, probleme);

	print_solution(bestRemplissage);
	//print_problemeBANDE(bestRemplissage);
	
	//liberer_probleme(probleme);
	//liberer_probleme(bestRemplissage);
	
	return 0;
}


