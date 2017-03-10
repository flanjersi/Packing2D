#include <stdio.h>
#include <stdlib.h>

#include "lib/ez-draw.h"
#include "lib/lecture.h"
#include "lib/objet.h"
#include "lib/bande.h"
#include "lib/boite.h"
#include "lib/probleme.h"
#include <string.h>

void set_color(OBJET objet){
    if(strcmp(objet->nom, "Rouge") == 0)
        ez_set_color(ez_red);
    else if(strcmp(objet->nom, "Vert") == 0)
        ez_set_color(ez_green);
    else if(strcmp(objet->nom, "Bleu") == 0)
        ez_set_color(ez_blue);
    else if(strcmp(objet->nom, "Cyan") == 0)
        ez_set_color(ez_cyan);
    else if(strcmp(objet->nom, "Jaune") == 0)
        ez_set_color(ez_yellow);
    else if(strcmp(objet->nom, "Gris") == 0)
        ez_set_color(ez_grey);
    else if(strcmp(objet->nom, "Noir") == 0)
        ez_set_color(ez_black);
    else if(strcmp(objet->nom, "Rose") == 0)
        ez_set_color(ez_magenta);
}


void win1_on_expose (Ez_event *ev)
{
    int surfaceRempli = 0;
    int x0, y0, x1, y1;
    int cptObjetInside = 0;
    int cptObjetRetourner = 0;
    int flagPrint = 0;   
    PROBLEME probleme = ez_get_data (ev->win);

    int surfaceTotal = probleme->boite->hauteur * probleme->boite->largeur;
    

    ez_set_color (ez_black);

    ez_draw_line(ev->win, 250,  220, probleme->boite->hauteur + 250,  220);
    ez_draw_line(ev->win, 250,  200, 250,  240);
    ez_draw_line(ev->win, probleme->boite->hauteur + 250,  200, probleme->boite->hauteur + 250,  240);

    for(int current_line = 0 ; current_line <= probleme->boite->hauteur/(probleme->boite->hauteur / 15) ; current_line++){
        int x_line = (probleme->boite->hauteur/15)*current_line + 250;
        ez_draw_text (ev->win, EZ_TL, x_line - 7, 180, "%d", (probleme->boite->hauteur/15)*current_line);
        ez_draw_line(ev->win, x_line,  210, x_line,  230);
    }

    for(int current_line = 0 ; current_line <= probleme->boite->largeur/(probleme->boite->largeur / 15) ; current_line++){
        int y_line = (probleme->boite->largeur/15)*current_line + 250;
        ez_draw_text (ev->win, EZ_TL, 180, y_line - 7, "%d", (probleme->boite->largeur/15)*current_line);
        ez_draw_line(ev->win, 210,  y_line, 230,  y_line);
    }

    ez_draw_line(ev->win, 220,  250, 220,  probleme->boite->largeur + 250);
    ez_draw_line(ev->win, 200,  250, 240,  250);
    ez_draw_line(ev->win, 200,  probleme->boite->largeur + 250, 240,  probleme->boite->largeur + 250);



    ez_draw_rectangle (ev->win, 250,  250, probleme->boite->hauteur + 250,  probleme->boite->largeur + 250);
    ez_set_color (ez_grey);

    printf("Objet non rentré : \n");

    for(int index_objet = 0 ; index_objet < probleme->nbObjets ; index_objet++){
        if(probleme->objets[index_objet]->positionX != -1 && probleme->objets[index_objet]->positionY != -1){      
            surfaceRempli += probleme->objets[index_objet]->largeur * probleme->objets[index_objet]->hauteur;

            x0 = 250 + probleme->objets[index_objet]->positionX ;
            y0 = 250 + probleme->objets[index_objet]->positionY ;
            
            if(probleme->objets[index_objet]->isRotate){
                x1 = x0 + probleme->objets[index_objet]->hauteur;
                y1 = y0 + probleme->objets[index_objet]->largeur;
                cptObjetRetourner++;
            }
            else{
                x1 = x0 + probleme->objets[index_objet]->largeur;
                y1 = y0 + probleme->objets[index_objet]->hauteur;
            }

            set_color(probleme->objets[index_objet]);
            ez_fill_rectangle(ev->win, x0, y0, x1, y1);
            ez_set_color(ez_black);
            ez_draw_rectangle(ev->win, x0, y0, x1, y1);
            //ez_draw_text (ev->win, EZ_TL, x0 + probleme->objets[index_objet]->largeur/4, y0 + probleme->objets[index_objet]->hauteur/3.5, "L = %d\nH = %d", probleme->objets[index_objet]->largeur, probleme->objets[index_objet]->hauteur);
            //ez_draw_text (ev->win, EZ_TL, x0 + probleme->objets[index_objet]->largeur/4, y0 + probleme->objets[index_objet]->hauteur/3.5, "%d", probleme->objets[index_objet]->indice);
            
            cptObjetInside++;

        }
        else{
            printf("\t");
            afficher_objet(probleme->objets[index_objet]);
        }
    }


    printf("\n\n");

    if(flagPrint == 0){
        printf("Objet entré : %d / %d\n", cptObjetInside, probleme->nbObjets);
        printf("Objet retourné : %d / %d\n", cptObjetRetourner, cptObjetInside);
        printf("Surface rempli %d / %d\n", surfaceRempli, surfaceTotal);
        flagPrint = 1;
    }

}

void win1_event (Ez_event *ev)
{
    switch (ev->type) {
        case Expose   : win1_on_expose    (ev); break;
    }
}

int main(){
	if (ez_init() < 0) exit(1);

    Ez_window win1;

    PROBLEME probleme = lectureSolution();
    
    win1 = ez_window_create (1000, 1000, "PACKING 2D", win1_event);

    ez_set_data(win1, probleme);

    ez_main_loop ();
    exit(0);

    return 0;
} 


