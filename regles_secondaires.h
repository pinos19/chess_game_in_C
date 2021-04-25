#ifndef REGLES_SECONDAIRES_H_INCLUDED
#define REGLES_SECONDAIRES_H_INCLUDED



void remplissage_tab_memoire(int valeur,int tab[],int taille_tab);
int gestion_roque(int Plateau[][8],int tab_piece_mem[],int *couleur,char *nom1,char *nom2,int n_Partie,int indice_ia,int couleur_ia);
int pat(int Plateau[][8],int couleur);
char *Changement_Pion(int Plateau[][8],int indice_ia,int couleur_courante,int couleur_ia);



#endif
