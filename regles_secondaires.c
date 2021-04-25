#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "outil.h"
#include "liste.h"
#include "pile.h"
#include "deplacement.h"
#include "gestion_ia.h"
#include "gestion_parties.h"
#include "regles_secondaires.h"

void remplissage_tab_memoire(int valeur,int tab[],int taille_tab){
    /*pour le roque il faut que le roi n'est pas bougé et
    que la tour n'est pas bougé non plus
    cette fonction enregistre les valeurs de pièce qui sont déplacés*/
    int i=0,existence=0;
    for(i=0;i<taille_tab;i++){
        if(tab[i]==valeur){
            existence =1;
        }
    }
    if(existence ==0){
        i=0;
        while(tab[i]!=0 && i<taille_tab){
            i++;
        }
        tab[i]=valeur;
    }
}
int gestion_roque(int Plateau[][8],int tab_piece_mem[],int *couleur,char *nom1,char *nom2,int n_Partie,int indice_ia,int couleur_ia){
    /*1 si le joueur choisit de roquer 0 si il ne veut pas*/
    int i,indice_roi=0,indice_tourg=0,indice_tourd=0,possibilite_pr=0,possibilite_gr=0,j,sortie=0,couleur_adverse,i_rd;
    Liste_possibilitees *liste=NULL;
    int p_e_p=0;
    char choix;
    char tab_ia[]="pgq";
    if(*couleur==1){
        if(Plateau[7][1]==0 && Plateau[7][2]==0 && Plateau[7][3]==0 && Plateau[7][0]==121 && Plateau[7][4]==161){
            possibilite_gr=1;
        }
        if(Plateau[7][5]==0 && Plateau[7][6]==0 && Plateau[7][4]==161 && Plateau[7][7]==122){
            possibilite_pr=1;
        }

        if(possibilite_gr==1 || possibilite_pr==1){
            couleur_adverse=2;
            for(i=0;i<8;i++){
                for(j=0;j<8;j++){
                    if((int)Plateau[i][j]/100 ==couleur_adverse){
                        /*les pièces adverses ne doit pas mettre en échec les cases entre le roi et la tour, roi et tour incluses*/
                        liste=Possibilite(Plateau,j,i,liste,*couleur,NULL,NULL,&p_e_p);
                        while(liste !=NULL){
                            if(liste->abscisse == 6 && liste->ordonnee == 7){
                                possibilite_pr=0;
                            }
                            if(liste->abscisse == 5 && liste->ordonnee == 7){
                                possibilite_pr=0;
                            }
                            if(liste->abscisse == 1 && liste->ordonnee == 7){
                                possibilite_gr=0;
                            }
                            if(liste->abscisse == 2 && liste->ordonnee == 7){
                                possibilite_gr=0;
                            }
                            if(liste->abscisse == 3 && liste->ordonnee == 7){
                                possibilite_gr=0;
                            }
                            liste=liste->suivant;
                        }
                    }
                }
            }
        }
        if(possibilite_gr==1 || possibilite_pr==1){
            for(i=0;i<40;i++){
                if(tab_piece_mem[i]==161){
                    indice_roi=1;
                    break;
                }
                if(tab_piece_mem[i]==121){
                    indice_tourg=1;
                }
                if(tab_piece_mem[i]==122){
                    indice_tourd=1;
                }
            }
            if(indice_roi==0){
                if(indice_tourd==0 && possibilite_pr==1 && indice_tourg==0 && possibilite_gr==1){

                    if(indice_ia==1 && *couleur==couleur_ia){
                        i_rd=rand()%3;
                        choix=tab_ia[i_rd];
                    }
                    else{
                        do{
                            printf("\nVous avez le choix entre :\n\tpetit roque(p)\n\tgrand roque(g)\n\tne pas roquer(q)\n votre choix(p/g/q) : ");
                            fflush(stdin);
                            scanf("%c",&choix);
                        }while(choix !='p' && choix != 'g' && choix !='q');
                    }




                    if(choix !='q'){
                        if(choix=='p'){
                            Plateau[7][6]=161;
                            Plateau[7][5]=122;
                            Plateau[7][7]=0;
                            Plateau[7][4]=0;
                            *couleur=2;
                            sortie=1;
                            raffraichissemente_ecran(Plateau,nom1,nom2,*couleur,1,n_Partie);
                            remplissage_tab_memoire(161,tab_piece_mem,40);
                            remplissage_tab_memoire(122,tab_piece_mem,40);
                            Sauvegarde(n_Partie,"PPPBB");

                        }
                        else{
                            Plateau[7][2]=161;
                            Plateau[7][3]=121;
                            Plateau[7][0]=0;
                            Plateau[7][4]=0;
                            *couleur=2;
                            sortie=1;
                            raffraichissemente_ecran(Plateau,nom1,nom2,*couleur,1,n_Partie);
                            remplissage_tab_memoire(161,tab_piece_mem,40);
                            remplissage_tab_memoire(121,tab_piece_mem,40);
                            Sauvegarde(n_Partie,"GGGBB");
                        }
                    }
                }
                if(indice_tourd==0 && possibilite_pr==1){
                    if(indice_ia==1 && *couleur==couleur_ia){
                        i_rd=rand()%2;
                        choix=tab_ia[i_rd];
                    }
                    else{
                        do{
                            printf("\nVous avez le choix entre :\n\tpetit roque(p)\n\tne pas roquer(q)\n votre choix(p/q) : ");
                            fflush(stdin);
                            scanf("%c",&choix);
                        }while(choix !='p' && choix !='q');
                    }

                    if(choix !='q'){
                        Plateau[7][6]=161;
                        Plateau[7][5]=122;
                        Plateau[7][7]=0;
                        Plateau[7][4]=0;
                        *couleur=2;
                        sortie=1;
                        raffraichissemente_ecran(Plateau,nom1,nom2,*couleur,1,n_Partie);
                        remplissage_tab_memoire(161,tab_piece_mem,40);
                        remplissage_tab_memoire(122,tab_piece_mem,40);
                        Sauvegarde(n_Partie,"PPPBB");
                    }
                }
                if(indice_tourg==0 && possibilite_gr==1){
                    if(indice_ia==1 && *couleur==couleur_ia){
                        i_rd=rand()%2;
                        choix=tab_ia[i_rd];
                    }
                    else{
                        do{
                            printf("\nVous avez le choix entre :\n\tgrand roque(g)\n\tne pas roquer(q)\n votre choix(g/q) : ");
                            fflush(stdin);
                            scanf("%c",&choix);
                        }while(choix != 'g' && choix !='q');
                    }

                    if(choix != 'q'){
                        Plateau[7][2]=161;
                        Plateau[7][3]=121;
                        Plateau[7][0]=0;
                        Plateau[7][4]=0;
                        *couleur=2;
                        sortie=1;
                        raffraichissemente_ecran(Plateau,nom1,nom2,*couleur,1,n_Partie);
                        remplissage_tab_memoire(161,tab_piece_mem,40);
                        remplissage_tab_memoire(121,tab_piece_mem,40);
                        Sauvegarde(n_Partie,"GGGBB");
                    }
                }
            }
        }
    }
    else{
        if(Plateau[0][1]==0 && Plateau[0][2]==0 && Plateau[0][3]==0 && Plateau[0][0]==221 && Plateau[0][4]==261){
            possibilite_gr=1;
        }
        if(Plateau[0][5]==0 && Plateau[0][6]==0 && Plateau[0][4]==261 && Plateau[0][7]==222){
            possibilite_pr=1;
        }

        if(possibilite_gr==1 || possibilite_pr==1){
            couleur_adverse=1;
            for(i=0;i<8;i++){
                for(j=0;j<8;j++){
                    if((int)Plateau[i][j]/100 ==couleur_adverse){
                        liste=Possibilite(Plateau,j,i,liste,*couleur,NULL,NULL,&p_e_p);
                        while(liste !=NULL){
                            if(liste->abscisse == 6 && liste->ordonnee == 0){
                                possibilite_pr=0;
                            }
                            if(liste->abscisse == 5 && liste->ordonnee == 0){
                                possibilite_pr=0;
                            }
                            if(liste->abscisse == 1 && liste->ordonnee == 0){
                                possibilite_gr=0;
                            }
                            if(liste->abscisse == 2 && liste->ordonnee == 0){
                                possibilite_gr=0;
                            }
                            if(liste->abscisse == 3 && liste->ordonnee == 0){
                                possibilite_gr=0;
                            }
                            liste=liste->suivant;
                        }
                    }
                }
            }
        }
        if(possibilite_gr==1 || possibilite_pr==1){
            for(i=0;i<40;i++){
                if(tab_piece_mem[i]==261){
                    indice_roi=1;
                    break;
                }
                if(tab_piece_mem[i]==221){
                    indice_tourg=1;
                }
                if(tab_piece_mem[i]==222){
                    indice_tourd=1;
                }
            }

            if(indice_roi==0){
                if(indice_tourd==0 && possibilite_pr==1 && indice_tourg==0 && possibilite_gr==1){
                    if(indice_ia==1 && *couleur==couleur_ia){
                        i_rd=rand()%3;
                        choix=tab_ia[i_rd];
                    }
                    else{
                        do{
                            printf("\nVous avez le choix entre :\n\tpetit roque(p)\n\tgrand roque(g)\n\tne pas roquer(q)\n votre choix(p/g/q) : ");
                            fflush(stdin);
                            scanf("%c",&choix);
                        }while(choix !='p' && choix != 'g' && choix !='q');
                    }


                    if(choix !='q'){
                        if(choix=='p'){
                            Plateau[0][6]=261;
                            Plateau[0][5]=222;
                            Plateau[0][7]=0;
                            Plateau[0][4]=0;
                            *couleur = 1;
                            sortie=1;
                            raffraichissemente_ecran(Plateau,nom1,nom2,*couleur,1,n_Partie);
                            remplissage_tab_memoire(261,tab_piece_mem,40);
                            remplissage_tab_memoire(222,tab_piece_mem,40);
                            Sauvegarde(n_Partie,"PPPNN");
                        }
                        else{
                            Plateau[0][2]=261;
                            Plateau[0][3]=221;
                            Plateau[0][0]=0;
                            Plateau[0][4]=0;
                            *couleur = 1;
                            sortie=1;
                            raffraichissemente_ecran(Plateau,nom1,nom2,*couleur,1,n_Partie);
                            remplissage_tab_memoire(261,tab_piece_mem,40);
                            remplissage_tab_memoire(221,tab_piece_mem,40);
                            Sauvegarde(n_Partie,"GGGNN");
                        }
                    }
                }
                if(indice_tourd==0 && possibilite_pr==1){
                    if(indice_ia==1 && *couleur==couleur_ia){
                        i_rd=rand()%2;
                        choix=tab_ia[i_rd];
                    }
                    else{
                        do{
                            printf("\nVous avez le choix entre :\n\tpetit roque(p)\n\tne pas roquer(q)\n votre choix(p/q) : ");
                            fflush(stdin);
                            scanf("%c",&choix);
                        }while(choix !='p' && choix !='q');
                    }



                    if(choix !='q'){
                        Plateau[0][6]=261;
                        Plateau[0][5]=222;
                        Plateau[0][7]=0;
                        Plateau[0][4]=0;
                        *couleur = 1;
                        sortie=1;
                        raffraichissemente_ecran(Plateau,nom1,nom2,*couleur,1,n_Partie);
                        remplissage_tab_memoire(261,tab_piece_mem,40);
                        remplissage_tab_memoire(222,tab_piece_mem,40);
                        Sauvegarde(n_Partie,"PPPNN");
                    }
                }
                if(indice_tourg==0 && possibilite_gr==1){
                    if(indice_ia==1 && *couleur==couleur_ia){
                        i_rd=rand()%2;
                        choix=tab_ia[i_rd];
                    }
                    else{
                        do{
                            printf("\nVous avez le choix entre :\n\tgrand roque(g)\n\tne pas roquer(q)\n votre choix(g/q) : ");
                            fflush(stdin);
                            scanf("%c",&choix);
                        }while(choix != 'g' && choix !='q');
                    }
                    if(choix != 'q'){
                        Plateau[0][2]=261;
                        Plateau[0][3]=221;
                        Plateau[0][0]=0;
                        Plateau[0][4]=0;
                        *couleur = 1;
                        sortie=1;
                        raffraichissemente_ecran(Plateau,nom1,nom2,*couleur,1,n_Partie);
                        remplissage_tab_memoire(261,tab_piece_mem,40);
                        remplissage_tab_memoire(221,tab_piece_mem,40);
                        Sauvegarde(n_Partie,"GGGNN");
                    }
                }
            }
        }

    }


    return sortie;
}
int pat(int Plateau[][8],int couleur){
    /*retourne 1 si il ya pat 0 sinon*/
    int i,j,sortie=1;
    int p_e_p=0;
    Liste_possibilitees *liste=NULL;
    for(i=0;i<8;i++){
        for(j=0;j<8;j++){
            if((int)Plateau[i][j]/100==couleur){
                liste=Possibilite(Plateau,j,i,liste,couleur,NULL,NULL,&p_e_p);
                if(liste!=NULL){
                    sortie=0;
                }
            }
        }
    }
    return sortie;
}
char *Changement_Pion(int Plateau[][8],int indice_ia,int couleur_courante,int couleur_ia){
    /*fonction qui permet de promouvoir un pion en dame, tour, roi, ou fou*/
    char wish;
    int i,ligne,colonne,N,T,i_rd;
    char tab_ia[]="TDFC";
    char *sortie;
    sortie=malloc(8*sizeof(char));
    for(ligne=0; ligne<8;ligne+=7){// Colonne 1 et 8 cf:Affichage
        for(colonne=0;colonne<8;colonne++){

            if((int)(Plateau[ligne][colonne]-100*((int)Plateau[ligne][colonne]/100))/10 == 1 ){//si le numero Type piece = Pions

                if(indice_ia==1 && couleur_courante==couleur_ia){
                    i_rd =rand()%4;
                    wish=tab_ia[i_rd];
                }else{
                    do
                    {
                        printf("\nQuelle piece voulez vous que le pion devienne ?(D F C T): ");
                        fflush(stdin);
                        scanf("%c",&wish);
                    }while(wish!='D' && wish!='F' && wish!='C' && wish!='T');
                }
                int C = (int)Plateau[ligne][colonne]/100; //Couleur

                switch (wish){
                    case 'T' :  T = 2;
                        break;
                    case 'C' :  T = 3;
                        break;
                    case 'F' :  T = 4;
                        break;
                    case 'D' :  T = 5;
                        break;
                }
                for(i=1;i<10;i++)
                {
                    if(existence_valeur(C*100+T*10+i,Plateau)==0)
                    {
                        N=i;
                        break;
                    }
                }
                Plateau[ligne][colonne] = C*100 + T*10 + N;
                char temp_piece[5];
                temp_piece[0]=wish;
                temp_piece[1]=wish;
                temp_piece[2]=(char)(N+48);
                temp_piece[3]='\0';
                strcpy(sortie,strcat(temp_piece,Coord_to_Nom(colonne,ligne)));
                return sortie;

            }
        }
    }
    return NULL;

}

////





////