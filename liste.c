
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "outil.h"
#include "liste.h"

Liste_possibilitees *insertion(Liste_possibilitees *liste,int abscisse,int ordonnee){
    /*permet d'inserer un nouvel element dans la liste utilise dans la fonction possibilite*/
    Liste_possibilitees *p=malloc(sizeof(Liste_possibilitees));
    p->abscisse = abscisse;
    p->ordonnee = ordonnee;
    p->suivant=NULL;
    if(liste==NULL)
    {
        return p;
    }
    else
    {
        p->suivant=liste;
        liste=p;
        return liste;
    }
}

void Affiche_possibilite(Liste_possibilitees *liste){
    /* le joueur entre le nom d'une piece et cette fonction lui affiche toutes les
    cases possibles pour la piece en question*/
    char *case_possible;
    while(liste!=NULL)
    {
        case_possible = Coord_to_Nom(liste->abscisse,liste->ordonnee);
        printf("%s\t",case_possible);
        liste=liste->suivant;
    }
}

int case_dans_liste(Liste_possibilitees *liste,char *case_rentree){
    /* retourne 1 si la case est dans la liste 0 sinon*/
    int sortie=0;
    while(liste!=NULL){
        if(strcmp(case_rentree,Coord_to_Nom(liste->abscisse,liste->ordonnee))==0){
            sortie=1;
            break;
        }


        liste=liste->suivant;
    }
    return sortie;


}


Liste_possibilitees *suppression(Liste_possibilitees *liste,Liste_possibilitees *transfert){
    if(liste==transfert){
        Liste_possibilitees *nv =liste->suivant;
        free(liste);
        return nv;
    }
    Liste_possibilitees *pointeur_precedent=liste;
    Liste_possibilitees *pointeur_actuel=liste;
    while(pointeur_actuel!=NULL && pointeur_actuel!=transfert){
        pointeur_precedent=pointeur_actuel;
        pointeur_actuel=pointeur_actuel->suivant;
    }
    pointeur_precedent->suivant = pointeur_actuel->suivant;
    free(pointeur_actuel);
    return liste;


}
int taille_liste(Liste_possibilitees *liste){
    int taille=0;
    while(liste!=NULL){

        taille++;
        liste=liste->suivant;
    }
    return taille;


}
void vider_liste(Liste_possibilitees *liste){
    if(liste!=NULL){
        Liste_possibilitees *next = liste->suivant;
        free(liste);
        vider_liste(next);
    }



}
