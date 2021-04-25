#ifndef JEU_H_INCLUDED
#define JEU_H_INCLUDED


void gestion_echec(int *couleur,int Plateau[][8],int *continuer,int *heure1,int *minute1,int *seconde1,int *heure2,int *minute2,int *seconde2,int *bg,int *ng,int *e,char *nom1,char *nom2,Pile **pile_depart,Pile **pile_fin,char couleur_choix_h,int n_Partie);
void jouer(int message);
void Menu(int *choix);
void actualiser_stats(char *Nom,int bg,int ng,int eq,int joueur);
void actualiser_statut(int n_Partie);
void regle(char *joueur1,char *joueur2);
void nouvellePartie();
void deroulement_jeu(int Plateau[][8],int *bg,int *ng,int *e,char *nom1,char *nom2,char couleur_choix_h,int n_Partie,int couleur_debut);
void aide();
int existJoueur(char * fichier,char *nom);
void modaliteAccess(char *nom,char *password,int nbJoueur,int message,char *couleur_choix_h);
int chekConnexion(char *nom,char*password);
void ajouterJoueur(char *fichier,char*nom);
void ajouterProfils( char *fichier,char *nom,char *password,int gagne,int perdue,int egalite);
void afficherProfil(char *nom);
void profil();
void voirProfil();
void affiche_tous_profils();
void changePassword();
void signin();
void actualiser_stats(char *Nom,int bg,int ng,int eq,int joueur);
void actualiser_statut(int n_Partie);
void regle(char *joueur1,char *joueur2);
void nouvellePartie();


#endif // JEU_H_INCLUDED
