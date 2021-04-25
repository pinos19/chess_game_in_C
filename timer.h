#ifndef TIMER_H_INCLUDED
#define TIMER_H_INCLUDED



void printData(int joueur,int heure1,int minute1,int seconde1,int heure2,int minute2,int seconde2,int Plateau[][8]);
void delay(int ms);
void counter(int *valeur,char *nom,int joueur,int caseoupiece,int *heure1,int *minute1,int *seconde1,int *heure2,int *minute2,int *seconde2,Liste_possibilitees *liste,int Plateau[][8],int echec);
void selection(int *valeur,char *nom);
void gagner_perdu(int joueur,int heure1,int minute1,int seconde1,int heure2,int minute2,int seconde2);
void SCC_GotoXY(int x, int y);
void setup_chrono(int *heure,int *minute,int Plateau[][8],char *nom1,char *nom2,int couleur,int n_Partie);
void raffraichissemente_ecran(int Plateau[][8],char *nom1,char *nom2,int couleur,int visu,int n_Partie);


#endif // TIMER_H_INCLUDED
