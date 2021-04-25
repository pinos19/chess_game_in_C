#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>


#include "outil.h"

void Traducteur(int code, char temp[]){ /*chaque piece du plateau se voit attribue une valeur unique, un int
                                            la fonction à partir de cet int remplit uun tableau de char pour donner une
                                            valeur intuitive de la piece ex: 210 ->nP0 (pion noir nP0*/



    int C = (int)code/100; //Couleur
    int T = (int)(code-100*C)/10; //Type
    int N = (int)code- 100*C - 10*T; //Numero
    switch(C){
        case 1:
            temp[0]='b'; // Blanc
            break;
        case 2:
            temp[0]='n'; // Noire
            break;
    }
    switch(T){
        case 1:
            temp[1]='P';// Pion
            break;
        case 2:
            temp[1]='T';// Tour
            break;
        case 3:
            temp[1]='C';// Cavalier
            break;
        case 4:
            temp[1]='F';// Fou
            break;
        case 5:
            temp[1]='D';// Reine (Dame)
            break;
        case 6:
            temp[1]='R';// Roi
            break;

    }
    temp[2]=(char)48+N;// Ascii pour passer le chiffre en char
    temp[3]='\0';

}

int Traducteur_Inv(char Piece[]){
    /*traduit chaine de caractere de la piece en forme int de la piece,
    exemple :  nP0-> 210 fonction utilitaire*/
    int n = 0;
    // Cas de la couleur
    switch (Piece[0]){
        case 'n' :  n += 200;
            break;
        case 'b' :  n += 100;
            break;
    }
    // Cas du type
    switch (Piece[1]){
        case 'P' :  n += 10;
            break;
        case 'T' :  n += 20;
            break;
        case 'C' :  n += 30;
            break;
        case 'F' :  n += 40;
            break;
        case 'D' :  n += 50;
            break;
        case 'R' :  n += 60;
            break;
    }
    // Cas du numero
    n += (int)Piece[2]-48;

    return n;
}

void Convertion_Plateau_Tableau(char *case_frappee,int *Pos){
    /* traduit case rentree style A1 et remplit un tableau
    deux dimensions style pour A1 par exemple on aura {0,0}, A2 on aura {0,1}*/

    char X = case_frappee[0];
    char Y = case_frappee[1];

    switch(X)
    {
        case 'A':
            Pos[0]=0;
            break;
        case 'B':
            Pos[0]=1;
            break;
        case 'C':
            Pos[0]=2;
            break;
        case 'D':
            Pos[0]=3;
            break;
        case 'E':
            Pos[0]=4;
            break;
        case 'F':
            Pos[0]=5;
            break;
        case 'G':
            Pos[0]=6;
            break;
        case 'H':
            Pos[0]=7;
            break;

    }
    // Cas Y

    Pos[1] = (int)Y-49 ;// Reference a la table ASCII

}

char *Coord_to_Nom(int abscisse,int ordonnee){
    /*fonction tres utile qui fait le lien entre le tableau de coordonnees remplit par les fonctions
    remplissage et la liste chainee; fonction passe d'une abscisse et d'une ordonnee a un tableau de char de
    la forme A1, B7...*/
    char *case_possible;
    case_possible = malloc(sizeof(char)*3);
    switch(abscisse)
    {
        case 0:
        case_possible[0]='A';
        break;
        case 1:
        case_possible[0]='B';
        break;
        case 2:
        case_possible[0]='C';
        break;
        case 3:
        case_possible[0]='D';
        break;
        case 4:
        case_possible[0]='E';
        break;
        case 5:
        case_possible[0]='F';
        break;
        case 6:
        case_possible[0]='G';
        break;
        case 7:
        case_possible[0]='H';
        break;
    }
    case_possible[1]=(char)ordonnee+49;
    case_possible[2]='\0';
    return case_possible;
}



void Initialisation(int Plateau[][8]){/*initialise le tableau avec les pieces en int*/
    for(int i = 0;i<8;i++){
        for(int j = 0;j<8;j++){
            int temp = 0 ;
        // definition de la couleur
            if(i==0 || i ==1){
              temp += 200;
          }
            else if(i==6 || i==7){
              temp += 100;
          }
        //initalisation des Pions
            if( i ==1 || i ==6 ) {
                temp += 10+j; // 10 -> Type Pion et j -> Numero Piece
            }
        //initalisation des Autres Piece
            else if(i ==0 || i ==7){
                switch(j){
                    // Tours
                    case 0:
                        temp +=21 ;
                        break;
                    case 7:
                        temp +=22 ;
                        break;

                    // Cavalier
                    case 1:
                        temp +=31 ;
                        break;
                    case 6:
                        temp +=32 ;
                        break;

                    // Fous
                    case 2:
                        temp += 41;
                        break;
                    case 5:
                        temp += 42;
                        break;

                    case 3: // Reine (Dame)
                        temp +=51 ;
                        break;
                    case 4: // Roi
                        temp +=61 ;
                        break;
                }

            }
            Plateau[i][j]=temp; // mis en place de la piece
        }
    }
}

void Recherche_piece(int tab[2],int nb_piece,int tableau[][8]){
    /*fonction utilitaire qui permet d'obtenir l'abscisse et l'ordonnee d'un piece en entrant sa
    valeur int, remplit un tableau*/
    int i,j;
    for(i=0;i<8;i++)
    {
        for(j=0;j<8;j++)
        {
            if(tableau[i][j]==nb_piece)
            {
                tab[0]=j;
                tab[1]=i;
            }
        }
    }
}
void Remplacer_abs_ord(int Plateau[][8],int abscisse1,int ordonnee1,int abscisse2,int ordonnee2,int *val){
    if(*val==0)
    {
        if(Plateau[ordonnee2][abscisse2] != 0)
        {
            *val = Plateau[ordonnee2][abscisse2];
        }
        Plateau[ordonnee2][abscisse2] = Plateau[ordonnee1][abscisse1];
        Plateau[ordonnee1][abscisse1] =0;
    }
    else
    {
        Plateau[ordonnee2][abscisse2] = Plateau[ordonnee1][abscisse1];
        Plateau[ordonnee1][abscisse1] = *val;

    }

}


void Remplacer(int Plateau[][8] ,char *case_voulue, char *case_initiale){ /*remplace la valeur de la case voulue par la case entree
                                                                            ,il n'y pas de verification,de savoir si le deplacement est possible
                                                                            , celles-ci etant faites en amont de l'appel de cette fonction PS: met a zero
                                                                            la valeur de la case entree*/
    int pos_voulue[2];
    int pos_initiale[2];
    int int_intermediaire;
    Convertion_Plateau_Tableau(case_voulue,pos_voulue);
    Convertion_Plateau_Tableau(case_initiale,pos_initiale);
    int_intermediaire=Plateau[pos_initiale[1]][pos_initiale[0]];
    Plateau[pos_initiale[1]][pos_initiale[0]]=0;
    Plateau[pos_voulue[1]][pos_voulue[0]] = int_intermediaire;

}

void Afficher(int Plateau[][8],char *nom1,char *nom2,int couleur,int visu,int n_Partie){/*appelle la fonction traducteur pour donner un plateau compréhensible*/
    int j,i,coloration;
    printf("                                PARTIE %d                             \n\n",n_Partie);
    printf("        A       B         C        D        E        F        G        H\n");
    printf("   |--------|--------|--------|--------|--------|--------|--------|--------|\n");
    for(i = 0;i<8;i++){
        printf("   |");
        for(j=0;j<8;j++){
            printf("        |");
        }
        printf("\n");
        printf(" %d |",i+1);// numero de ligne
        for(j = 0;j<8;j++){
            if(Plateau[i][j] == 0){ //si la case est libre
                printf("        |");
            }else{
                char temp[4];
                Traducteur(Plateau[i][j],temp);
                if((int)Plateau[i][j]/100==1){
                    coloration=46;
                }
                else{
                    coloration=61;
                }
                printf("   ");
                Color(coloration,coloration);
                printf("%s",temp);
                Color(31,31);
                printf("  |");
            }

        }
        if(i==1){
            printf("\t%s",nom2);
        }
        if(i==6){
            printf("\t%s",nom1);
        }
        printf("\n");
        printf("   |");
        for(j=0;j<8;j++){
            printf("        |");
        }
        printf("\n");
        printf("   |--------|--------|--------|--------|--------|--------|--------|--------|\n");
    }
    if(visu==1){
        if(couleur==1){
            printf("\n\tC'est au tour de %s",nom1);
        }
        else if(couleur==2){
            printf("\n\tC'est au tour de %s",nom2);
        }
    }


}
void affiche_tab_pur(int Plateau[][8]){
    int i,j;
    for(i=0;i<8;i++)
    {
        for(j=0;j<8;j++)
        {
            printf("%d\t",Plateau[i][j]);
        }
        printf("\n");
    }
}
int changement_couleur(int couleur){
    if(couleur ==1)
    {
        couleur =2;
    }
    else
    {
        couleur =1;
    }
    return couleur;
}
int existence_valeur(int valeur,int Plateau[][8]){
    /*la valeur existe 0 la valeur n'existe pas
    teste si une pièce a été mangé ou no en soit*/

    int i,j;
    for(i=0;i<8;i++)
    {
        for(j=0;j<8;j++)
        {
            if(Plateau[i][j]==valeur)
            {
                return 1;
            }
        }
    }
    return 0;
}
void Color(int couleurDuTexte,int couleurDeFond){
    /*modifie la couleur de l'affichage en console */
        HANDLE H=GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(H,couleurDeFond*16+couleurDuTexte);
}

//////////////////////

////////////////

void recherche_element_vide(int *x,int *y,int Plateau[][8]){//fonction pour revenir en jeu apres une saisie 'q'
    int i,j;
    for(i=0;i<8;i++){
        for(j=0;j<8;j++){
            if(Plateau[i][j]==0){
                *x=j;
                *y=i;
                break;
            }
        }
    }

}
int Plateau_egalite(int PlateauRef[][8],int PlateauTemp[][8]){
    int i,j;
    int sortie=1;
    for(i=0;i<8;i++){
        for(j=0;j<8;j++){
            if(PlateauRef[i][j]!=PlateauTemp[i][j]){
                sortie=0;
                break;
            }
        }
    }
    return sortie;




}
void raffraichissemente_ecran(int Plateau[][8],char *nom1,char *nom2,int couleur,int visu,int n_Partie){/* raffraichit l'écran utilisation de system("cls)*/
    system("cls");
    Afficher(Plateau,nom1,nom2,couleur,visu,n_Partie);

}
