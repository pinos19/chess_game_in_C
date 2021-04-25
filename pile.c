#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "pile.h"

void vider_pile(Pile *haut_de_pile){
    if(haut_de_pile!=NULL){
        Pile *next=haut_de_pile->suivant;
        free(haut_de_pile);
        vider_pile(next);
    }



}
Pile *empiler(Pile *haut_de_pile,char *casep){
    Pile *nouveau = malloc(sizeof(Pile));
    if(haut_de_pile==NULL){
        strcpy(nouveau->casep,casep);
        nouveau->suivant=NULL;
    }
    else{
        strcpy(nouveau->casep,casep);
        nouveau->suivant=haut_de_pile;
    }
    return nouveau;
}
void afficher(Pile *pile_case){
    while(pile_case!=NULL){
        printf("%s\n",pile_case->casep);


        pile_case=pile_case->suivant;
    }


}
