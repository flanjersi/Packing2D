#include <stdio.h>
#include <stdlib.h>

#include "lib/objet.h"
#include "lib/bande.h"
#include "lib/boite.h"
#include "lib/lecture.h"
#include "lib/sac_a_dos.h"
#include "lib/probleme.h"
#include "lib/remplir_boite.h"

int main(void){
	
	PROBLEME remplissageCourrant = lecture();
	//print_probleme(remplissageCourrant);
	bestRemplissage = cree_probleme(0,
									remplissageCourrant->boite->hauteur, 
									remplissageCourrant->boite->largeur);



	remplir_boite(remplissageCourrant->boite->largeur ,  
						2, remplissageCourrant, 1);
	//print_problemeBANDE(bestRemplissage);


	print_solution(bestRemplissage);



	return 0;
}

