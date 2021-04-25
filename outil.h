#ifndef OUTIL_H_INCLUDED
#define OUTIL_H_INCLUDED

void Traducteur(int code ,char temp[]);
int Traducteur_Inv(char Piece[]);
void Convertion_Plateau_Tableau(char *case_frappee,int *Pos);
char *Coord_to_Nom(int abscisse,int ordonnee);
void Initialisation(int Plateau[][8]);
void Recherche_piece(int tab[2],int nb_piece,int tableau[][8]);
void Remplacer_abs_ord(int Plateau[][8],int abscisse1,int ordonnee1,int abscisse2,int ordonnee2,int *val);
void Remplacer(int Plateau[][8] ,char *case_voulue, char *case_initiale);
void Afficher(int Plateau[][8],char *nom1,char *nom2,int couleur,int visu,int n_Partie);
void affiche_tab_pur(int Plateau[][8]);
int changement_couleur(int couleur);
int existence_valeur(int valeur,int Plateau[][8]);
void Color(int couleurDuTexte,int couleurDeFond);
void raffraichissemente_ecran(int Plateau[][8],char *nom1,char *nom2,int couleur,int visu,int n_Partie);
void recherche_element_vide(int *x,int *y,int Plateau[][8]);
int Plateau_egalite(int PlateauRef[][8],int PlateauTemp[][8]);



#endif // OUTIL_H_INCLUDED
