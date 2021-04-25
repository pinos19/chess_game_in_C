#ifndef LISTE_H_INCLUDED
#define LISTE_H_INCLUDED





  /*liste chainee; chaque element de la liste enregistre une position precise(abscisse+ordonnee)*/
struct Liste_possibilitees
{
    int abscisse;
    int ordonnee;
    struct Liste_possibilitees *suivant;
};
typedef struct Liste_possibilitees Liste_possibilitees;
Liste_possibilitees *suppression(Liste_possibilitees *liste,Liste_possibilitees *transfert);
Liste_possibilitees *insertion(Liste_possibilitees *liste,int abscisse,int ordonnee);
int case_dans_liste(Liste_possibilitees *liste,char *case_rentree);
void Affiche_possibilite(Liste_possibilitees *liste);
int taille_liste(Liste_possibilitees *liste);
void vider_liste(Liste_possibilitees *liste);

#endif // LISTE_H_INCLUDED
