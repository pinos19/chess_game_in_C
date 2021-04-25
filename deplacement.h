#ifndef DEPLACEMENT_H_INCLUDED
#define DEPLACEMENT_H_INCLUDED


Liste_possibilitees *Possibilite_modifie(int Plateau[][8] ,int X ,int Y,Liste_possibilitees *liste);
Liste_possibilitees *Possibilite(int Plateau[][8] ,int X ,int Y,Liste_possibilitees *liste,int couleur,Pile *pile_depart,Pile *pile_fin,int *p_e_p);
void remplissage_cases_pion(int tab_coordonnees[][2],int *nb_case,int abscisse,int ordonnee,int couleur,int Plateau[][8],int *e_p,Pile *depart_case,Pile *fin_case);
void remplissage_cases_tour(int tab_coordonnees[][2],int *nb_case,int abscisse,int ordonnee,int couleur,int Plateau[][8],int *j);
void remplissage_cases_cavalier(int tab_coordonnees[][2],int *nb_case,int abscisse,int ordonnee,int couleur,int Plateau[][8]);
void remplissage_cases_fou(int tab_coordonnees[][2],int *nb_case,int abscisse,int ordonnee,int couleur,int Plateau[][8],int j);
void remplissage_cases_roi(int tab_coordonnees[][2],int *nb_case,int abscisse,int ordonnee,int couleur,int Plateau[][8]);
int test_echec(int Plateau[][8],int couleur);



#endif // DEPLACEMENT_H_INCLUDED
