#ifndef GESTION_IA_H_INCLUDED
#define GESTION_IA_H_INCLUDED


int lettre_ou_chiffre(char caractere);
int adaptateur(char lettre);
void reducteur(char *entree,char *piece,char *casep,int couleur,int Plateau[][8],char *sup,Pile **pile_depart,Pile **pile_fin);
void ecriture(char *temp,int *i,char *chaine);
void affinage_base_de_donnees();
void piece_et_case_aleatoire(char *casep,char *piece,int Plateau[][8],int couleur);
void Changement_Pion_ia(int Plateau[][8],char sup);

#endif // GESTION_IA_H_INCLUDED
