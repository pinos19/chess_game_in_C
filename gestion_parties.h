#ifndef GESTION_PARTIES_H_INCLUDED
#define GESTION_PARTIES_H_INCLUDED

void Sauvegarde_init(int Partie, char *J1, char *J2);
void Sauvegarde(int Partie, char * element);
void Chargement(int Partie_num ,int Plateau[][8],char *J_1,char *J_2,int *couleur);
void Revisualisation(int Partie_num);
void fonction_gestion_coup(char *entree,int Plateau[][8],int *couleur);
int Partie_Dispo();
int Partie_Existe(int n_Partie);
#endif // GESTION_PARTIES_H_INCLUDED
