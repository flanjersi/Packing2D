#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int nargs, char **arg){
  int hauteurBoite, largeurBoite, nbObjects, graine, tailleMinObjet, tailleMaxObjet;

  int nbCouleurs = 8;
  char *tabchar[] = { "Rouge", "Vert", "Bleu", "Cyan", "Jaune", "Gris", "Noir", "Rose"};
  
  if(nargs != 7){
    printf("Le format de ce générateur est : <largeurBoite> <hauteurBoite> <nbOjets> <tailleMin Objet> <tailleMax Objet> <graine>\n");
    exit(0);
  }
  
  hauteurBoite = atoi(arg[1]);
  largeurBoite = atoi(arg[2]);
  nbObjects = atoi(arg[3]);
  tailleMinObjet = atoi(arg[4]);
  tailleMaxObjet = atoi(arg[5]);
  graine = atoi(arg[6]);
  srand(graine);
  
  printf("%d %d\n", largeurBoite, hauteurBoite);
  printf("%d\n", nbObjects);
  
  for( int object = 0 ; object < nbObjects ; object++)
  	printf("%s %d %d\n", tabchar[rand()%nbCouleurs], 
        rand() % (tailleMaxObjet - tailleMinObjet) + tailleMinObjet, 
        rand() % (tailleMaxObjet - tailleMinObjet) + tailleMinObjet);


  return 0;	
}