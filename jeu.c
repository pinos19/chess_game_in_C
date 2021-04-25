
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>


#include "outil.h"
#include "liste.h"
#include "pile.h"
#include "deplacement.h"
#include "gestion_ia.h"
#include "gestion_parties.h"
#include "timer.h"
#include "regles_secondaires.h"
#include "jeu.h"


void gestion_echec(int *couleur,int Plateau[][8],int *continuer,int *heure1,int *minute1,int *seconde1,int *heure2,int *minute2,int *seconde2,int *bg,int *ng,int *e,char *nom1,char *nom2,Pile **pile_depart,Pile **pile_fin,char couleur_choix_h,int n_Partie){
    int i,j,echec_mat=1,bonne_piece=1,erreur=1,nombre_piece=-1,valeur1=1,valeur2=1,echec=1;
    int tab_position_piece[2];
    Liste_possibilitees *liste=NULL;
    char piece[5],case_entree[3],*case_piece;
    Liste_possibilitees *liste3=NULL;
    int p_e_p;
    char sortie;
    char chaine_save[4];
    char *chgmt_pion;
    int X,Y;
    for(i=0;i<8;i++){
        for(j=0;j<8;j++){
            if((int)Plateau[i][j]/100 == *couleur){
                liste=Possibilite(Plateau,j,i,liste,*couleur,*pile_depart,*pile_fin,&p_e_p);
                if(liste!=NULL){
                    echec_mat=0;
                }

            }
        }
    }
    p_e_p=0;
    int indice_ia=0;
    int couleur_ia=0;
    if(strcmp(nom2,"ordinateur")==0){
        indice_ia=1;
        if(couleur_choix_h=='b'){
            couleur_ia=2;
        }
        else{
            couleur_ia=1;
        }

    }



    /*jusqu'ici on enregistre la valeur en int des pieces qui peuvent empecher l'echec dans le tableau "tab_piece" ainsi, le joueur ne
    peut deplacer que certaines pieces. De plus on enregistre les cases qui empechent l'echec dans la liste "liste2",on peut avoir des doublons
    style : D2  D2  ... on n'a pas besoin de savoir quelle case vient de quelle piece, ce n'est pas necessaire pour le bon fonctionnement. Dernier
    point, si on a "tab_piece" qui n'a comme valeur que des 0, c'est un echec et mat, utile pour la suite.*/


    if(echec_mat==0){
        do{
            if(indice_ia==0 || (indice_ia==1 && *couleur!=couleur_ia)){
                while(valeur1){
                    counter(&valeur1,piece,*couleur,1,heure1,minute1,seconde1,heure2,minute2,seconde2,liste,Plateau,echec);
                }
            }
            if(indice_ia==1 && *couleur==couleur_ia){
                piece_et_case_aleatoire(case_entree,piece,Plateau,*couleur);

            }
            if(strcmpi(piece,"Q")==0){
                printf("Partie %d sauvegarde avec success\nEtes vous sur de vouloir quitter ?(o/n) : ",n_Partie);
                fflush(stdin);
                scanf("%c",&sortie);
                if(sortie=='o' || sortie =='O'){
                    jouer(0);
                }
                raffraichissemente_ecran(Plateau,nom1,nom2,*couleur,1,n_Partie);
            }
            else{
                nombre_piece = Traducteur_Inv(piece);
                Recherche_piece(tab_position_piece,nombre_piece,Plateau);
                X=tab_position_piece[0];
                Y=tab_position_piece[1];
                case_piece=Coord_to_Nom(tab_position_piece[0],tab_position_piece[1]);
                liste3 = Possibilite(Plateau,tab_position_piece[0],tab_position_piece[1],liste3,*couleur,*pile_depart,*pile_fin,&p_e_p);
                if((int)nombre_piece/100 == *couleur){
                    if(liste3!=NULL){
                        *pile_depart = empiler(*pile_depart,case_piece);
                        if(indice_ia==0 || (indice_ia==1 && *couleur!=couleur_ia)){
                            while(valeur2){
                                counter(&valeur2,case_entree,*couleur,2,heure1,minute1,seconde1,heure2,minute2,seconde2,liste3,Plateau,echec);
                            }
                        }
                        valeur2=1;
                        do{
                            char *case_coord;
                            case_coord=Coord_to_Nom(liste3->abscisse,liste3->ordonnee);//modif liste->4 en liste->3
                            if(strcmp(case_entree,case_coord)==0){
                                *pile_fin=empiler(*pile_fin,case_entree);
                                Remplacer(Plateau,case_entree,case_piece);
                                erreur=0;
                                break;
                            }
                            liste3=liste3->suivant;
                        }while(liste3!=NULL);
                        if(erreur){
                            raffraichissemente_ecran(Plateau,nom1,nom2,*couleur,1,n_Partie);
                            printf("\ncase invalide");
                        }
                        else{/*prise en passant */
                            Sauvegarde(n_Partie,strcat(piece,case_entree));
                            if(p_e_p==1){
                                Plateau[Y][X+1]=0;
                                strcpy(chaine_save,"DPP");
                                Sauvegarde(n_Partie,strcat(chaine_save,Coord_to_Nom(X,Y)));
                            }
                            else if(p_e_p==-1){
                                Plateau[Y][X-1]=0;
                                strcpy(chaine_save,"GPP");
                                Sauvegarde(n_Partie,strcat(chaine_save,Coord_to_Nom(X,Y)));
                            }

                            *couleur = changement_couleur(*couleur);
                            raffraichissemente_ecran(Plateau,nom1,nom2,*couleur,1,n_Partie);
                            chgmt_pion = Changement_Pion(Plateau,indice_ia,*couleur,couleur_ia);
                            if(chgmt_pion!=NULL){
                                Sauvegarde(n_Partie,chgmt_pion);
                            }


                        }
                        bonne_piece=0;
                    }
                    else{
                        raffraichissemente_ecran(Plateau,nom1,nom2,*couleur,1,n_Partie);
                        printf("\nVous ne pouvez pas jouez cette piece");
                    }
                }
                else{
                    raffraichissemente_ecran(Plateau,nom1,nom2,*couleur,1,n_Partie);
                    if(*couleur ==1){
                        printf("\nc'est au tour des blancs !");
                    }
                    else{
                        printf("\nc'est au tour des noirs !");
                    }
                }

            }
            valeur1=1;
        }while(bonne_piece);
    }
    else{                                          /*si condition echec et mat valide, on vient ici*/
        raffraichissemente_ecran(Plateau,nom1,nom2,*couleur,0,n_Partie);
        printf("\nECHEC ET MAT");

        if(*couleur==1){
            *ng=1;
            printf("\tLes noirs ont gagne\n");
        }
        else{
            *bg=1;
            printf("\tLes blancs ont gagne\n");
        }
        *continuer =0;
    }
}

void deroulement_jeu(int Plateau[][8],int *bg,int *ng,int *e,char *nom1,char *nom2,char couleur_choix_h,int n_Partie,int couleur){
    /*partie joueur contre joueur*/
    int continuer = 1,valeur1=1,valeur2=1,piece,erreur_case=1,p_e_p=0,X,Y,indice_ia=0,couleur_ia=0;
    char piece_entree[4],case_voulue[3],chaine_save[4];
    int tab_pos_piece[2];
    int tab_memoire_pieces_jouees[40]={0};
    Liste_possibilitees *liste=NULL;
    Pile *depart_case=NULL;
    Pile *fin_case=NULL;
    char *chgmt_pion;
    char sortie;
    if(strcmp(nom2,"ordinateur")==0 || strcmp(nom1,"ordinateur")==0){
        indice_ia=1;
        if(couleur_choix_h=='b'){
            couleur_ia=2;
        }
        else{
            couleur_ia=1;
        }
        if(existJoueur("joueurs.txt","ordinateur")==0){
            ajouterJoueur("joueurs.txt","ordinateur");
            ajouterProfils("profiljoueurs.txt","ordinateur","ordinateur",0,0,0);
        }
    }
    int heure1=0,minute1=0,seconde1=0,heure2=0,minute2=0,seconde2=0;
    setup_chrono(&heure1,&minute1,Plateau,nom1,nom2,couleur,n_Partie);
    heure2=heure1;
    minute2=minute1;
    seconde2=seconde1;
    while(continuer){
        if(test_echec(Plateau,couleur)){
            gestion_echec(&couleur,Plateau,&continuer,&heure1,&minute1,&seconde1,&heure2,&minute2,&seconde2,bg,ng,e,nom1,nom2,&depart_case,&fin_case,couleur_choix_h,n_Partie);
        }
        else{
            if(pat(Plateau,couleur)==0){
                if(gestion_roque(Plateau,tab_memoire_pieces_jouees,&couleur,nom1,nom2,n_Partie,indice_ia,couleur_ia)==0){
                        do{
                        if(indice_ia==0 || (indice_ia==1 && couleur!=couleur_ia)){
                            while(valeur1){
                                counter(&valeur1,piece_entree,couleur,1,&heure1,&minute1,&seconde1,&heure2,&minute2,&seconde2,liste,Plateau,0);
                            }
                        }
                        else if(indice_ia==1 && couleur_ia==couleur){
                            piece_et_case_aleatoire(case_voulue,piece_entree,Plateau,couleur);
                        }
                        if(strcmpi(piece_entree,"Q")==0){
                            printf("Partie %d sauvegarde avec success\nEtes vous sur de vouloir quitter ?(o/n) : ",n_Partie);
                            fflush(stdin);
                            scanf("%c",&sortie);
                            if(sortie=='o' || sortie =='O'){
                                jouer(0);
                            }
                            else{
                                recherche_element_vide(tab_pos_piece,tab_pos_piece+1,Plateau);
                            }
                        }
                        else{
                            piece = Traducteur_Inv(piece_entree);
                            Recherche_piece(tab_pos_piece,piece,Plateau);
                            X=tab_pos_piece[0];
                            Y=tab_pos_piece[1];
                            if((int)Plateau[tab_pos_piece[1]][tab_pos_piece[0]]/100!=couleur){
                                raffraichissemente_ecran(Plateau,nom1,nom2,couleur,1,n_Partie);
                                printf("\nVous ne pouvez pas deplacer les pieces de l'adversaire.\n ");
                            }
                        }
                        valeur1=1;
                    }while((int)Plateau[tab_pos_piece[1]][tab_pos_piece[0]]/100!=couleur);
                    remplissage_tab_memoire(piece,tab_memoire_pieces_jouees,40);
                    liste = Possibilite(Plateau,tab_pos_piece[0],tab_pos_piece[1],liste,couleur,depart_case,fin_case,&p_e_p);
                    depart_case = empiler(depart_case,Coord_to_Nom(tab_pos_piece[0],tab_pos_piece[1]));
                    if(liste != NULL){
                        if(indice_ia==0 || (indice_ia==1 && couleur!=couleur_ia)){
                            while(valeur2){
                                counter(&valeur2,case_voulue,couleur,2,&heure1,&minute1,&seconde1,&heure2,&minute2,&seconde2,liste,Plateau,0);
                            }
                        }
                        valeur2=1;
                        while(liste!=NULL){
                            if(strcmpi(case_voulue,Coord_to_Nom(liste->abscisse,liste->ordonnee))==0){
                                erreur_case=0;
                            }
                            liste=liste->suivant;
                        }
                        if(erreur_case){
                            raffraichissemente_ecran(Plateau,nom1,nom2,couleur,1,n_Partie);
                            printf("\ncases impossible a atteindre");
                        }
                        else{
                            fin_case = empiler(fin_case,case_voulue);
                            Remplacer(Plateau,case_voulue,Coord_to_Nom(tab_pos_piece[0],tab_pos_piece[1]));
                            Sauvegarde(n_Partie,strcat(piece_entree,case_voulue));
                            chgmt_pion = Changement_Pion(Plateau,indice_ia,couleur,couleur_ia);
                            if(chgmt_pion!=NULL){
                                Sauvegarde(n_Partie,chgmt_pion);
                            }
                            if(p_e_p==1){
                                Plateau[Y][X+1]=0;
                                strcpy(chaine_save,"DPP");
                                Sauvegarde(n_Partie,strcat(chaine_save,Coord_to_Nom(X,Y)));
                            }
                            else if(p_e_p==-1){
                                Plateau[Y][X-1]=0;
                                strcpy(chaine_save,"GPP");
                                Sauvegarde(n_Partie,strcat(chaine_save,Coord_to_Nom(X,Y)));
                            }
                            couleur=changement_couleur(couleur);
                            raffraichissemente_ecran(Plateau,nom1,nom2,couleur,1,n_Partie);
                        }
                    }
                    else{
                        raffraichissemente_ecran(Plateau,nom1,nom2,couleur,1,n_Partie);
                        printf("\npas de mouvements possibles pour cette piece");
                    }
                    liste=NULL;
                    erreur_case=1;
                    }
            }
            else{
                printf("\n Il y PAT, c'est un match nul ");
                *e=1;
                continuer=0;
            }
        }
    }
    printf("Tapez une touche pour retourner au menu");
    while(!kbhit()){
    }
}
void Menu(int *choix){
    /*menu principal*/
    int a;
    do{
        printf("*********Menu**********\n");
        printf("1) Jouer une nouvelle partie\n");
        printf("2) Reprendre une partie\n");
        printf("3) Revisualisation d'une partie\n");
        printf("4) Profils\n");
        printf("5) aide\n");
        printf("6) Quitter\n");
        printf("Entrez votre choix : ");
        scanf("%d",&a);
        if(a!=1 && a!=2 && a!=3 && a!=4 && a!=5 && a!=6){
            system("cls");
            printf("\tSAISIE INVALIDE\n\n");
        }
        *choix=a;
    }while(a!=1 && a!=2 && a!=3 && a!=4 && a!=5 && a!=6);
}
void actualiser_stats(char *Nom,int bg,int ng,int eq,int joueur){
    /* permet d'actualiser les stats des joueurs dans les fichiers*/
    char nom[35],ancien[35];
    int g,p,e;

    FILE *f= fopen("profiljoueurs.txt","r");
    FILE *f1=fopen("temp.txt","a");

    while(fscanf(f,"%s %s %d %d %d",nom,ancien,&g,&p,&e)!= EOF){
        if(strcmp(Nom,nom)!=0){
            fprintf(f1,"%s %s %d %d %d\n",nom,ancien,g,p,e);
        }
        else{
            if(joueur==1){
                fprintf(f1,"%s %s %d %d %d\n",nom,ancien,g+bg,p+ng,e+eq);
            }
            else{
                fprintf(f1,"%s %s %d %d %d\n",nom,ancien,g+ng,p+bg,e+eq);
            }
        }
    }
    fclose(f);
    fclose(f1);
    remove("profiljoueurs.txt");
    rename("temp.txt","profiljoueurs.txt");
}
void actualiser_statut(int n_Partie){
    int stutu=1;
    char nom_fichier[100];
    sprintf(nom_fichier,"Partie_%d.txt",n_Partie);
    FILE *fichier = fopen(nom_fichier,"a");
    fprintf(fichier,"%d",stutu);
    fclose(fichier);

}
void jouer(int message){
    system("cls");
    int choix;
    char rep;
    int n_Partie;
    if(message==1){
        printf("Vous ne pouvez pas jouer cette partie, elle a ete jouee par d'autres joueurs\n");
    }
    else if(message==2){
        printf("Cette partie est terminee, vous ne pouvez pas la rejouer\n");
    }
    Menu(&choix);
    switch(choix){
        case 1 :
            nouvellePartie();
            break;
        case 2:
            printf("Quelle Partie Souhaitez-vous reprendre ? : ");

            int bg=0,ng=0,e=0;
            scanf("%d",&n_Partie);
            int Plateau[8][8];
            char couleur_choix_h='0';
            int couleur,num_partie;
            Initialisation(Plateau);
            char nom1[35],nom2[35];
            char joueur1[35],joueur2[35];
            while(Partie_Existe(n_Partie)==0 ){
                system("cls");
                printf("Partie %d est Inexistante\n",n_Partie);
                printf("Quelle Partie Souhaitez-vous reprendre ? : ");
                scanf("%d",&n_Partie);
            }
            ///on lit le dernier caractere pour savoir si la partie est terminee ou non
            char nom_partie[100];
            int caractere;
            sprintf(nom_partie,"Partie_%d.txt",n_Partie);
            FILE *fichier=fopen(nom_partie,"r");
            fseek(fichier,-1,SEEK_END);
            caractere=fgetc(fichier);
            fclose(fichier);
            if(caractere==49){
                jouer(2);
            }
            FILE *fichier2=fopen(nom_partie,"r");
            fscanf(fichier2,"Partie %d :Joueur %s / Joueur %s \n",&num_partie,joueur1,joueur2);
            fclose(fichier2);
            printf("\nEntrez le nom du joueur 1 : ");
            scanf("%s",nom1);
            printf("\nEntrez le nom du joueur 2 : ");
            scanf("%s",nom2);
            if((strcmp(nom1,joueur1)==0 && strcmp(nom2,joueur2)==0) || (strcmp(nom1,joueur2)==0 && strcmp(nom2,joueur1)==0)){
                couleur=1;
                Chargement(n_Partie,Plateau,joueur1,joueur2,&couleur);
                if(strcmp(joueur1,nom1)==0){
                    couleur_choix_h='b';
                    deroulement_jeu(Plateau,&bg,&ng,&e,nom1,nom2,couleur_choix_h,n_Partie,couleur);
                    actualiser_stats(nom1,bg,ng,e,1);
                    actualiser_stats(nom2,bg,ng,e,2);
                    actualiser_statut(n_Partie);

                }else{
                    deroulement_jeu(Plateau,&bg,&ng,&e,nom2,nom1,couleur_choix_h,n_Partie,couleur);
                    actualiser_stats(nom1,bg,ng,e,2);
                    actualiser_stats(nom2,bg,ng,e,1);
                    actualiser_statut(n_Partie);

                }
                jouer(0);
            }
            else{
                jouer(1);
            }


            break;
        case 3:
            printf("Quelle Partie Souhaitez-vous Revisualiser ? : ");
            scanf("%d",&n_Partie);

            while(Partie_Existe(n_Partie)==0 ){
                system("cls");
                printf("Partie %d est Inexistante",n_Partie);
                printf("Quelle Partie Souhaitez-vous Revisualiser ?: ");
                scanf("%d",&n_Partie);
            }
            Revisualisation(n_Partie);
            jouer(0);




            break;
        case 4:
            profil();
            break;
        case 5:
            aide();
            printf("\n\nTapez une touche pour sortir :");
            while(!kbhit()){

            }
            jouer(0);
            break;
        case 6:
            system("cls");
            printf("voulez vous vraiment quiter (o/n)? : ");
            fflush(stdin);
            scanf("%c",&rep);
            if(rep!='n'){
                exit(0);
            }
            else{
                jouer(0);
            }
            break;
    }
}
void nouvellePartie(){
    int bg=0,ng=0,e=0;
    int Plateau[8][8];
    char nom1[35],password1[35];
    char nom2[35],password2[35];
    char couleur_choix_h;
    system("cls");
    modaliteAccess(nom1,password1,1,0,&couleur_choix_h);
    system("cls");
    modaliteAccess(nom2,password2,2,0,&couleur_choix_h);
    if(couleur_choix_h=='n'){
        system("cls");
        regle(nom2,nom1);
        int n_Partie =Partie_Dispo();
        Sauvegarde_init(n_Partie,nom2,nom1);
        Initialisation(Plateau);
        deroulement_jeu(Plateau,&bg,&ng,&e,nom2,nom1,couleur_choix_h,n_Partie,1);
        actualiser_stats(nom1,bg,ng,e,2);
        actualiser_stats(nom2,bg,ng,e,1);
        actualiser_statut(n_Partie);
    }
    else{
        system("cls");
        regle(nom1,nom2);
        int n_Partie =Partie_Dispo();
        Sauvegarde_init(n_Partie,nom1,nom2);
        Initialisation(Plateau);
        deroulement_jeu(Plateau,&bg,&ng,&e,nom1,nom2,couleur_choix_h,n_Partie,1);
        actualiser_stats(nom1,bg,ng,e,1);
        actualiser_stats(nom2,bg,ng,e,2);
        actualiser_statut(n_Partie);
    }

}
void regle(char *joueur1,char *joueur2){
    printf("*****************Regle*****************\n");
    printf("1) Vous allez jouer une nouvelle partie\n");
    printf("2) Vous pouvez quitter la partie a tout moment en appuyant sur 'q'\n");
    printf("3) %s joue avec les pieces blanches\n",joueur1);
    printf("4) %s joue avec les pieces noires\n",joueur2);

}
void aide(){
    printf("\n\nRegles du jeu\n\n1)	Les deplacements\n\nDans les echecs il y a 6 six types de piece, les pions, les tours, les cavaliers, les dames et le roi. Le plateau est un damier de 8 cases par 8. Le pion peut se deplacer d'une case en ligne droite ou de deux cases s'il n'a jamais ete deplace. Le pion mange d'une case a sa droite ou a sa gauche, le pion est la seule piece qui se deplace d'une maniere et mange d'une autre, pour les autres pieces, ce sera la meme chose. Le cavalier se deplace en L de trois cases, il peut se deplacer meme si il y a une piece dans son chemin, c'est la seule piece qui peut se deplacer au-dessus d'une autre. La tour se deplace sur toute la longueur d'une ligne ou d'un colonne. Le fou lui se deplace sur les diagonales. La dame combine les deplacements de la tour et ceux du fou, elle peut aller en diagonales, en ligne et en colonne. Enfin le roi lui se deplace d'une seule case autour de lui.\nDonc ça c'est pour ce qui est des deplacements\n\n2)	La promotion\n\nLa promotion est une regle qui lorsqu'un pion se situe sur la premiere ligne ou la derniere ligne du damier, doit etre change en une piece superieure (tour, cavalier, fou ou dame), ce qui fait qu'en theorie un joueur peut avoir 9 dames, ou 10 tours ou 10 fous, etc\n\n3)	La prise en passant\n\nLa prise en passant est encore une regle avec les pions. Si un pion blanc est en 4eme ligne et qu'un pion noir avance de deux cases de maniere à ce qu'a la fin du tour les deux pions soient cote a cote, alors le pion blanc, au prochain tour peut manger le pion noir. Ce coup est symetrique bien entendu, les noirs comme les blancs peuvent le faire. Le raisonnement derriere ce coup apparemment etrange est en fait tres logique, on a simplement pris le pion alors qu'il passait, comme s'il n'avait avance que d'une seule case, et donc avant qu'il n'ait eu le temps d'avancer d'une 2e case. Ceci explique aussi pourquoi ce coup n'est possible que pour le coup joue immediatement apres.\n\n4)	Le grand roque et le petit roque\n\nLe grand roque et le petit roque sont des coups qui necessitent 3 conditions. Les roques s'effectuent avec le roi et la tour gauche ou droite. Premiere condition, il faut que les cases qui les separent soient vides. Deuxieme condition il faut que le roi ne soit pas en echec et qu'apres le coup il ne le soit pas non plus, il faut aussi que la tour ne soit pas en echec apres le coup avant elle peut l'etre. Troisieme et derniere condition, aucune des deux pieces ne doit avoir bouge avant le coup.\n\n5)	L'echec et l'echec et mat\n\nL'echec consiste a attaquer le roi ennemi avec une piece. L'echec et mat s'applique lorsque quelque soit le coup joue par l'adversaire, le roi reste en echec, il signe la fin de la partie. Une autre regle fondamentale en lien avec l'echec est le fait que on ne peut pas se mettre en echec soit meme ça peut paraitre evident mais c'est une regle.\n\n6)	Le pat\n\nLe pat est une position dans laquelle le joueur n'est pas en echec mais il ne peut faire aucun coup sans mettre son roi en echec. Un pat signe un arret de la partie et un match nul.");


}
void modaliteAccess(char *nom,char *password,int nbJoueur,int message,char *couleur_choix_h){
    /*menu avant de joueur à la partie*/
    int choix;
    char rep;

    printf("*************Joueur %d ************\n ",nbJoueur);
    if(message==1){
        printf("Votre choix est invalide\n");
    }
    if(message==2){
        printf("Desole, vous ne pouvez pas vous connecter, vos informations sont incorrectes, verifiez votre login ou  votre password\n");
    }
    if(message==3){
        printf("Desole, ce 'login' existe deja choisissez en un autre\n");
    }
    do{

        printf("Etes vous deja membre ou voulez vous vous enregistrer?\n ");
        if(nbJoueur==2){
            printf("1) Jouer contre l'ordinateur\n ");
            printf("2) Deja membre\n ");
            printf("3) S'enregistrer\n ");
            printf("4) Menu\n ");
            printf("5) Quitter\n ");
            printf("Entrez votre choix :");
        }
        else{
            printf("1) Deja membre\n ");
            printf("2) S'enregistrer\n ");
            printf("3) Menu\n ");
            printf("4) Quitter\n ");
            printf("Entrez votre choix :");
        }






        scanf("%d",&choix);
        if(choix!=1 && choix!=2 && choix!=3 && choix!=4){
            system("cls");
            printf("saisie invalide,reesayez\n");
        }
    }while(choix!=1 && choix!=2 && choix!=3 && choix!=4);
    if(nbJoueur==2){
        choix--;
    }

    switch(choix){
        case 0:
            do{
                printf("Choisissez la couleur que vous voulez jouer (b/n) :");
                fflush(stdin);
                scanf("%c",couleur_choix_h);
            }while(*couleur_choix_h !='b' && *couleur_choix_h !='n');


            strcpy(nom,"ordinateur");
            strcpy(password,"ordinateur");
            break;
        case 1 :
            printf("Login :");
            scanf("%s",nom);
            printf("\nPassword :");
            scanf("%s",password);
            if(chekConnexion(nom,password)!=1){
                system("cls");
                modaliteAccess(nom,password,nbJoueur,2,NULL);
            }
            break;
        case 2:
            printf("Login :");
            scanf("%s",nom);
            printf("\nPassword :");
            scanf("%s",password);
            if(existJoueur("joueurs.txt",nom)){
                system("cls");
                modaliteAccess(nom,password,nbJoueur,3,NULL);
            }
            else{
                ajouterJoueur("joueurs.txt",nom);
                ajouterProfils("profiljoueurs.txt",nom,password,0,0,0);
            }
            break;
       case 3:
            jouer(0);
            break;
       case 4:
            system("cls");
            printf("voulez vous vraiment quiter (o/n)? : ");
            fflush(stdin);
            scanf("%c",&rep);
            if(rep!='n'){
                exit(0);
            }
            else{
                system("cls");
                modaliteAccess(nom,password,nbJoueur,0,NULL);
            }
            break;
        }

}
int chekConnexion(char *nom,char*password){
    /* 1 si c'est bon 0 sinon*/
    char Nom[35];char Password[35];
    int g,p,e;
    FILE *f= fopen("profiljoueurs.txt","r");
    fseek(f,0,SEEK_SET);
    while(fscanf(f,"%s %s %d %d %d",Nom,Password,&g,&p,&e)!= EOF){
        if(strcmp(Nom,nom)==0){
            if(strcmp(Password,password)==0){
                fclose(f);
                return 1;
            }
        }
    }
    fclose(f);
    return 0;
}
int existJoueur(char * fichier,char *nom){
    char Nom[35];
    FILE *f= fopen(fichier,"r");
    fseek(f,0,SEEK_SET);
    while(fscanf(f,"%s",Nom)!= EOF)
    {
        if(strcmp(Nom,nom)==0){
            fclose(f);
            return 1;
        }
    }
    fclose(f);
    return 0;
}
void ajouterJoueur(char *fichier,char*nom){
    FILE *f1= fopen(fichier,"a");
    fprintf(f1,"%s\n",nom);
    fclose(f1);
}
void ajouterProfils( char *fichier,char *nom,char *password,int gagne,int perdue,int egalite){

        FILE *f1= fopen(fichier,"a");
        fprintf(f1,"%s %s %d %d %d\n",nom,password,gagne,perdue,egalite);
        fclose(f1);
}
void profil(){
    int choix ;
    system("cls");
    do{
        printf("******************Profil******************\n");
        printf("1) Voir son profil\n");
        printf("2) Voir tous les profils et leur stats\n");
        printf("3) Changer password\n");
        printf("4) S'enregistrer\n");
        printf("5) Menu\n");
        printf("Entrez votre choix : ");
        scanf("%d",&choix);
        if(choix!=1 && choix!=2 && choix !=3 && choix !=4 && choix!=5 && choix!=6){
            system("cls");
            printf("erreur saisie\n");
        }
    }while(choix!=1 && choix!=2 && choix !=3 && choix !=4 && choix!=5 && choix!=6);
    switch(choix){
        case 1:
            voirProfil();
            break;
        case 2 :
            affiche_tous_profils();
            break;
        case 3 :
            changePassword();
            break;
        case 4 :
            signin();
            break;
        case 5 :
            jouer(0);
            break;
    }
}
void voirProfil(){
    char password[35];char login[35];
    char arriere,rep,reessayer;
    printf("Entrez vos donnees de profil\n");
    printf("login : ");
    scanf("%s",login);
    printf("\npassword : ");
    scanf("%s",password);
    if(chekConnexion(login,password)!=1){
        do{
            system("cls");
            printf("*********informations de connexion incorrectes*********\n");
            printf("Reessayer (o/n)? : ");
            fflush(stdin);
            scanf("%c",&reessayer);
        }while(reessayer!='o' && reessayer!='n');
        if(reessayer=='o'){
            voirProfil();
        }
        else{
            profil();
        }
    }

    else{
        int choix;

        do{
            system("cls");
            afficherProfil(login);
            printf("\n revenir en arriere (o/n)?");
            fflush(stdin);
            scanf("%c",&arriere);
        }while(arriere!='o');


        do{
            system("cls");
            printf("\n1) Profil \n");
            printf("2) Quitter \n");
            printf("Entrez votre choix : ");
            scanf("%d",&choix);
            if(choix!=1 && choix!=2){
                system("cls");
                printf("erreur saisie\n");
            }
        }while(choix!=1 && choix!=2);
        switch(choix){
            case 1:
                profil();
                break;
            case 2 :
                system("cls");
                printf("voulez vous vraiment quiter (o/n)? : ");
                fflush(stdin);
                scanf("%c",&rep);
                if(rep!='n'){
                    exit(0);
                }
                else{
                    profil();;
                }
                break;
        }
    }
}
void afficherProfil(char *nom){
    char Nom[35];
    char Password[35];
    int g,e,p;
    FILE *f= fopen("profiljoueurs.txt","r");
    while(fscanf(f,"%s %s %d %d %d",Nom,Password,&g,&p,&e)!= EOF)
    {   if(strcmp(Nom,nom)==0)
        {
           printf("Votre login est : %s\n",nom);
           printf("Votre Password est : %s\n",Password);
           printf("vous avez gagne %d partie(s) \n",g);
           printf("vous avez perdu %d partie(s) \n",p);
           printf("Vous avez %d egalite(s)  \n",e);
        }
    }
}
void affiche_tous_profils(){
    char login[35],password[35];
    char arriere;
    int v,d,e;

    FILE *f=fopen("profiljoueurs.txt","r");
    system("cls");
    while(fscanf(f,"%s %s %d %d %d",login,password,&v,&d,&e)!=EOF){
        printf("%s a %d victoire(s), %d defaite(s) et %d nul(s)\n",login,v,d,e);
    }
    do{
        printf("\n revenir en arriere (o/n)? : ");
        fflush(stdin);
        scanf("%c",&arriere);
        if(arriere !='o'){
            system("cls");
        }
    }while(arriere !='o');
    profil();

}
void changePassword(){
    char Nom[35],Password[35],nouveau[35],ancien[35],nom [35];
    int g,e,p;
    char rep;
    system("cls");
    printf("login : ");
    scanf("%s",Nom);
    printf("\nAncien password : ");
    scanf("%s",Password);


    printf("\nNouveau password : ");
    scanf("%s",nouveau);


    if(chekConnexion(Nom,Password)!=1){
        changePassword();
    }
    else{
        FILE *f= fopen("profiljoueurs.txt","r");
        FILE *f1=fopen("temp.txt","w");

        while(fscanf(f,"%s %s %d %d %d",nom,ancien,&g,&p,&e)!= EOF){
            if(strcmp(Nom,nom)!=0){
                fprintf(f1,"%s %s %d %d %d\n",nom,ancien,g,p,e);
            }
            else{
                fprintf(f1,"%s %s %d %d %d\n",nom,nouveau,g,p,e);
            }
        }
        fclose(f);
        fclose(f1);
        remove("profiljoueurs.txt");
        rename("temp.txt","profiljoueurs.txt");
        int choix;
        system("cls");
        printf("mot de passe change avec succes\n");
        do{
            printf("1) Menu  \n");
            printf("2) Profil \n");
            printf("3) Changer mot de passe \n");
            printf("4) Quitter \n");
            printf("Entrez votre choix : ");
            scanf("%d",&choix);
            if(choix>4 || choix <1){
                system("cls");
                printf("Erreur saisie\n");
            }
        }while(choix>4 || choix <1);
        switch(choix){
            case 1:
                jouer(0);
                break;
            case 2 :
                profil();
                break;
            case 3 :
                changePassword();
                break;
            case 4 :
                system("cls");
                printf("voulez vous vraiment quiter (o/n)? : ");
                fflush(stdin);
                scanf("%c",&rep);
                if(rep!='n'){
                    exit(0);
                }
                else{
                    changePassword();
                }
                break;
        }

    }
}
void signin(){
   char nom[53],password[53];int choix;
   char rep;
   system("cls");
   printf("Login : ");
   scanf("%s",nom);
   printf("Password : ");
   scanf("%s",password);
   if(existJoueur("joueurs.txt",nom)){
        system("cls");
        printf("Ce joueur existe deja choisissez un autre nom\n");
   }
   else{
        ajouterJoueur("joueurs.txt",nom);
        ajouterProfils("profiljoueurs.txt",nom,password,0,0,0);
   }
    do{
        printf("\n1) Menu  \n");
        printf("2) Profil \n");
        printf("3) Quitter \n");
        printf("Votre choix : ");
        scanf("%d",&choix);
        if(choix<1 || choix >3){
            system("cls");
            printf("Erreur saisie\n");
        }
    }while(choix<1 || choix >3);
    switch(choix){
        case 1:
            jouer(0);
            break;
        case 2:
            profil();
            break;
        case 3:
            system("cls");
            printf("voulez vous vraiment quiter (o/n)? : ");
            fflush(stdin);
            scanf("%c",&rep);
            if(rep!='n'){
                exit(0);
            }
            else{
                profil();
            }
            break;
    }
}
