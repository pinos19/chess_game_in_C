#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <conio.h>
#include <ctype.h>
#include <windows.h>

#include "outil.h"
#include "pile.h"
#include "liste.h"
#include "deplacement.h"
#include "gestion_ia.h"
#include "gestion_parties.h"


int Partie_Existe(int n_Partie){

    char nom_fichier[100];
    sprintf(nom_fichier,"Partie_%d.txt",n_Partie);
    FILE *fichier = fopen(nom_fichier,"r");

    if(fichier != NULL){
        fclose(fichier);
        return 1; // la partie existe
    }else{
        fclose(fichier);
        return 0; // la partie existe pas
    }
}

int Partie_Dispo(){

    FILE * fichier = fopen("Parties.txt","r+");

    if(fichier != NULL){
        int temp;

        fscanf(fichier,"%d\n",&temp);
        rewind(fichier);//retour au debut fichier
        fprintf(fichier,"%d\n",temp+1);
        fclose(fichier);
        return temp+1;
    }else{
        fclose(fichier);
        fichier = fopen("Parties.txt","w");
        fprintf(fichier,"1\n");
        fclose(fichier);

        return 1;
    }
}

void Sauvegarde_init(int Partie, char *J1, char *J2){ // J1 J2 sont des IDs
    // gestion du nom du fichier de partie
    char temp[100];
    sprintf(temp,"Partie_%d.txt",Partie);

    // Initialisation du fichier partie
    FILE * fichier = fopen(temp,"w");
    if(fichier != NULL){
        fprintf(fichier,"Partie %d :Joueur %s / Joueur %s \n",Partie,J1,J2);

    }else{
        printf("Erreur d'ouverture du ficher de sauvegarde");
    }

    fclose(fichier);
}

void Sauvegarde(int Partie, char * element){

    char temp[100];
    sprintf(temp,"Partie_%d.txt",Partie);
    FILE * fichier = fopen(temp,"a");

    if(element != NULL){

        fprintf(fichier,"%s ",element);
        fclose(fichier);
    }else{
        printf("Erreur element vide") ;
    }
}

void Chargement(int Partie_num ,int Plateau[][8],char *J_1,char *J_2,int *couleur){
    /* a_qui_de_jouer sert a savoir qui reprend la partie la fin du chargement:
        -> 1 Noir
        -> -1 Blanc*/
    char chaine[2500];
    char * nom_fichier= malloc(100*sizeof(char));
    sprintf(nom_fichier,"Partie_%d.txt",Partie_num);
    FILE *fichier = fopen(nom_fichier,"r");
    fgets(chaine,2500,fichier);
    fgets(chaine,2500,fichier);
    int i=0;
    int l=0;
    char piece_et_case_temp[6];
    while(chaine[i]!='\0'){
        if(chaine[i]==' '){
            piece_et_case_temp[l]='\0';
            fonction_gestion_coup(piece_et_case_temp,Plateau,couleur);
            l=0;
        }else{
            piece_et_case_temp[l]=chaine[i];
            l++;

        }
        i++;
    }

}
void Revisualisation(int n_Partie){

    char * nom_fichier= malloc(100*sizeof(char));
    sprintf(nom_fichier,"Partie_%d.txt",n_Partie);
    FILE *fichier = fopen(nom_fichier,"r");
    char nom1[35],nom2[35];

    fscanf(fichier,"Partie %d :Joueur %s / Joueur %s \n",&n_Partie,nom1,nom2);
    fseek(fichier,0,SEEK_SET);

    char chaine1[100];
    char chaine2[7];
    int taille;

    fgets(chaine1,100,fichier);
    taille = strlen(chaine1);
    int Plateau[8][8];
    Initialisation(Plateau);
    int couleur=1;
    char saisie;
    char Touche;
    int coup=0;
    int i;


    //Détermination du mode de revisualisation
    do{
        printf("Visualisation Automatique (a) ou  Manuelle (m):");
        fflush(stdin);
        scanf("%c",&Touche);
    }while(toupper(Touche)!='A' && toupper(Touche)!='M');
    //Systeme de Visualisation Auto
    if(Touche == 'a' || Touche == 'A'){
            // temps d'attente
        do{
            if(fgets(chaine2,7,fichier)!=NULL){
                system("cls");
                chaine2[5]='\0';
                fonction_gestion_coup(chaine2,Plateau,&couleur);
                Afficher(Plateau,nom1,nom2,couleur,0,n_Partie);
                Sleep(3000); //Pause de 1 seconde

            }
            else{
                system("cls");
                Afficher(Plateau,nom1,nom2,couleur,0,n_Partie);
                printf("Vous etes au bout de la partie, tapez une touche pour sortir : ");
                while(!kbhit()){
                }
                break;


            }
        }while(1);

    //Systeme de Visualisation Manuel
    }else if(Touche == 'm'|| Touche == 'M'){

        do{
            printf("suivant (s) precedent (p) quitter (q): ");
            fflush(stdin);
            scanf("%c",&saisie);
            if(saisie=='s' || saisie=='S'){
                if(fgets(chaine2,7,fichier)!=NULL){
                    coup++;
                    chaine2[5]='\0';
                    fonction_gestion_coup(chaine2,Plateau,&couleur);
                    system("cls");
                    Afficher(Plateau,nom1,nom2,couleur,0,n_Partie);
                }
                else{
                    system("cls");
                    Afficher(Plateau,nom1,nom2,couleur,0,n_Partie);
                    printf("Vous etes au bout de la partie\n");
                }

                }
                else if(saisie=='p' || saisie=='P'){
                    coup--;
                    if(coup<0){
                        coup=0;
                    }
                    Initialisation(Plateau);
                    fseek(fichier,taille+1,SEEK_SET);
                    for(i=0;i<coup;i++){
                        fgets(chaine2,7,fichier);
                        chaine2[5]='\0';
                        fonction_gestion_coup(chaine2,Plateau,&couleur);
                    }
                    system("cls");
                    Afficher(Plateau,nom1,nom2,couleur,0,n_Partie);
                }

        }while(saisie!='q' && saisie!='Q');
    }

}

void fonction_gestion_coup(char *piece_et_case_temp,int Plateau[][8],int *couleur){
    char casep[3];
    char piece[4];
    int tab[2];
    int piece_int;
    if(piece_et_case_temp[0]=='G'){
        if(piece_et_case_temp[4]=='N'){
            Remplacer(Plateau,"D1","A1");
            Remplacer(Plateau,"C1","E1");
            *couleur=changement_couleur(*couleur);
        }
        else if(piece_et_case_temp[4]=='B'){
            Remplacer(Plateau,"D8","A8");
            Remplacer(Plateau,"C8","E8");
            *couleur=changement_couleur(*couleur);
        }
        else if(lettre_ou_chiffre(piece_et_case_temp[4])==-1){
            casep[0]=piece_et_case_temp[3];
            casep[1]=piece_et_case_temp[4];
            casep[2]='\0';
            Convertion_Plateau_Tableau(casep,tab);
            Plateau[tab[1]][tab[0]-1]=0;
        }
    }
    else if(piece_et_case_temp[0]=='P'){
        if(piece_et_case_temp[4]=='N'){
            Remplacer(Plateau,"G1","E1");
            Remplacer(Plateau,"F1","H1");
            *couleur=changement_couleur(*couleur);
        }
        else if(piece_et_case_temp[4]=='B'){
            Remplacer(Plateau,"G8","E8");
            Remplacer(Plateau,"F8","H8");
            *couleur=changement_couleur(*couleur);
        }
    }
    else if(piece_et_case_temp[0]=='D'){
        if(piece_et_case_temp[1]=='P'){
            casep[0]=piece_et_case_temp[3];
            casep[1]=piece_et_case_temp[4];
            casep[2]='\0';
            Convertion_Plateau_Tableau(casep,tab);
            Plateau[tab[1]][tab[0]+1]=0;
        }
        else if(piece_et_case_temp[1]=='D'){
            casep[0]=piece_et_case_temp[3];
            casep[1]=piece_et_case_temp[4];
            casep[2]='\0';
            if(casep[1]=='1'){
                piece_int = 150 + ((int)piece_et_case_temp[2]-48);
            }
            else if(casep[1]=='8'){
                piece_int = 250 + ((int)piece_et_case_temp[2]-48);
            }
            Convertion_Plateau_Tableau(casep,tab);
            Plateau[tab[1]][tab[0]]=piece_int;
        }

    }
    else if(piece_et_case_temp[0]=='n' || piece_et_case_temp[0]=='b'){
        strncpy(piece,piece_et_case_temp,3);
        casep[0]=piece_et_case_temp[3];
        casep[1]=piece_et_case_temp[4];
        casep[2]='\0';
        piece_int = Traducteur_Inv(piece);
        Recherche_piece(tab,piece_int,Plateau);
        Remplacer(Plateau,casep,Coord_to_Nom(tab[0],tab[1]));
        *couleur=changement_couleur(*couleur);
    }
    else if(piece_et_case_temp[0]=='T'){
        casep[0]=piece_et_case_temp[3];
        casep[1]=piece_et_case_temp[4];
        casep[2]='\0';
        if(casep[1]=='1'){
            piece_int = 120 + ((int)piece_et_case_temp[2]-48);
        }
        else if(casep[1]=='8'){
            piece_int = 220 + ((int)piece_et_case_temp[2]-48);
        }
        Convertion_Plateau_Tableau(casep,tab);
        Plateau[tab[1]][tab[0]]=piece_int;
    }
    else if(piece_et_case_temp[0]=='C'){
        casep[0]=piece_et_case_temp[3];
        casep[1]=piece_et_case_temp[4];
        casep[2]='\0';
        if(casep[1]=='1'){
            piece_int = 130 + ((int)piece_et_case_temp[2]-48);
        }
        else if(casep[1]=='8'){
            piece_int = 230 + ((int)piece_et_case_temp[2]-48);
        }
        Convertion_Plateau_Tableau(casep,tab);
        Plateau[tab[1]][tab[0]]=piece_int;
    }
    else if(piece_et_case_temp[0]=='F'){
        casep[0]=piece_et_case_temp[3];
        casep[1]=piece_et_case_temp[4];
        casep[2]='\0';
        if(casep[1]=='1'){
            piece_int = 140 + ((int)piece_et_case_temp[2]-48);
        }
        else if(casep[1]=='8'){
            piece_int = 240 + ((int)piece_et_case_temp[2]-48);
        }
        Convertion_Plateau_Tableau(casep,tab);
        Plateau[tab[1]][tab[0]]=piece_int;
    }

}
