#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#include "outil.h"
#include "pile.h"
#include "liste.h"
#include "deplacement.h"
#include "gestion_ia.h"


void reducteur(char *entree,char *piece,char *casep,int couleur,int Plateau[][8],char *sup,Pile **pile_depart,Pile **pile_fin){
    /*fonction qui traduit une entrée style Rd4 en (nT1) pour la pièce
    et D4 pour la case, b6 en (nP1) et B2 pour la case ia avancé pas eu le temps de la finir*/

    Liste_possibilitees *liste=NULL;
    int piece_tempo,i,p_e_p=0,X,Y,colonne_ou_ligne;
    int tab_position_piece[2];
    *sup='0';

    if(lettre_ou_chiffre(entree[0])==1 && lettre_ou_chiffre(entree[1])==-1){//case où le pion avance tout droit, promotion possible
        casep[0]=toupper(entree[0]);
        casep[1]=((int)'9'-(int)entree[1])+48;
        casep[2]='\0';
        for(i=0;i<8;i++){
            piece_tempo = couleur*100+10+i;
            if(existence_valeur(piece_tempo,Plateau)){
                Recherche_piece(tab_position_piece,piece_tempo,Plateau);
                X=tab_position_piece[0];
                Y=tab_position_piece[1];
                liste=Possibilite_modifie(Plateau,X,Y,liste);
                if(case_dans_liste(liste,casep)){
                    Traducteur(piece_tempo,piece);
                    break;
                }
            }
        }
        if(entree[2]=='='){
            switch(entree[3]){
                case 'Q':
                    *sup='D';
                    break;
                case 'N':
                    *sup='C';
                    break;
                case 'B':
                    *sup='F';
                    break;
                case 'R':
                    *sup='T';
                    break;

            }
        }
        Remplacer(Plateau,casep,Coord_to_Nom(X,Y));
        Changement_Pion_ia(Plateau,*sup);
        *pile_depart = empiler(*pile_depart,Coord_to_Nom(X,Y));
        *pile_fin = empiler(*pile_fin,casep);
    }
    else if(lettre_ou_chiffre(entree[0])==1 && lettre_ou_chiffre(entree[1])==0){//cas où le pion mange il peut y avoir promotion suite à cela
        casep[0]=toupper(entree[2]);
        casep[1]=((int)'9'-(int)entree[3])+48;
        casep[2]='\0';
        colonne_ou_ligne = adaptateur(entree[0]);
        for(i=0;i<8;i++){
            piece_tempo = couleur*100+10+i;
            if(existence_valeur(piece_tempo,Plateau)){
                Recherche_piece(tab_position_piece,piece_tempo,Plateau);
                X=tab_position_piece[0];
                Y=tab_position_piece[1];
                liste=Possibilite(Plateau,X,Y,liste,couleur,*pile_depart,*pile_fin,&p_e_p);
                if(case_dans_liste(liste,casep)){
                    if(X==colonne_ou_ligne){
                        Traducteur(piece_tempo,piece);
                        break;
                    }
                }
            }
        }
        if(entree[4]=='='){
            switch(entree[5]){
                case 'Q':
                    *sup='D';
                    break;
                case 'N':
                    *sup='C';
                    break;
                case 'B':
                    *sup='F';
                    break;
                case 'R':
                    *sup='T';
                    break;

            }
        }
        Remplacer(Plateau,casep,Coord_to_Nom(X,Y));
        Changement_Pion_ia(Plateau,*sup);
        *pile_depart = empiler(*pile_depart,Coord_to_Nom(X,Y));
        *pile_fin = empiler(*pile_fin,casep);
        if(p_e_p==1){
            Plateau[Y][X+1]=0;
        }
        else if(p_e_p==-1){
            Plateau[Y][X-1]=0;
        }
    }
    else if(entree[0]=='R'){
        if(lettre_ou_chiffre(entree[2])==-1 || lettre_ou_chiffre(entree[1])==0){//tour d�placement avec manger pas d'ambiguit�
            if(lettre_ou_chiffre(entree[1])==1){
                casep[0]=toupper(entree[1]);
                casep[1]=((int)'9'-(int)entree[2])+48;
                casep[2]='\0';
            }
            else if(lettre_ou_chiffre(entree[1])==0){
                casep[0]=toupper(entree[2]);
                casep[1]=((int)'9'-(int)entree[3])+48;
                casep[2]='\0';
            }
            for(i=1;i<10;i++){
                piece_tempo = couleur*100+20+i;
                if(existence_valeur(piece_tempo,Plateau)){
                    Recherche_piece(tab_position_piece,piece_tempo,Plateau);
                    X=tab_position_piece[0];
                    Y=tab_position_piece[1];
                    liste=Possibilite(Plateau,X,Y,liste,couleur,*pile_depart,*pile_fin,&p_e_p);
                    if(case_dans_liste(liste,casep)){
                        Traducteur(piece_tempo,piece);
                        break;
                    }
                }
            }
            Remplacer(Plateau,casep,Coord_to_Nom(X,Y));
            *pile_depart = empiler(*pile_depart,Coord_to_Nom(X,Y));
            *pile_fin = empiler(*pile_fin,casep);
        }
        else if(lettre_ou_chiffre(entree[2])==1){//déplacement ambigue sans manger
            colonne_ou_ligne = adaptateur(entree[1]);
            casep[0]=toupper(entree[2]);
            casep[1]=((int)'9'-(int)entree[3])+48;
            casep[2]='\0';

            if(lettre_ou_chiffre(entree[1])==1){
                for(i=1;i<10;i++){
                    piece_tempo = couleur*100+20+i;
                    if(existence_valeur(piece_tempo,Plateau)){
                        Recherche_piece(tab_position_piece,piece_tempo,Plateau);
                        X=tab_position_piece[0];
                        Y=tab_position_piece[1];
                        liste=Possibilite(Plateau,X,Y,liste,couleur,*pile_depart,*pile_fin,&p_e_p);
                        if(case_dans_liste(liste,casep)){
                            if(X==colonne_ou_ligne){
                                Traducteur(piece_tempo,piece);
                                break;
                            }
                        }
                    }
                }
            }
            else if(lettre_ou_chiffre(entree[1])==-1){
                for(i=1;i<10;i++){
                    piece_tempo = couleur*100+20+i;
                    if(existence_valeur(piece_tempo,Plateau)){
                        Recherche_piece(tab_position_piece,piece_tempo,Plateau);
                        X=tab_position_piece[0];
                        Y=tab_position_piece[1];
                        liste=Possibilite(Plateau,X,Y,liste,couleur,*pile_depart,*pile_fin,&p_e_p);
                        if(case_dans_liste(liste,casep)){
                            if(Y==colonne_ou_ligne){
                                Traducteur(piece_tempo,piece);
                                break;
                            }
                        }
                    }
                }
            }

            Remplacer(Plateau,casep,Coord_to_Nom(X,Y));
            *pile_depart = empiler(*pile_depart,Coord_to_Nom(X,Y));
            *pile_fin = empiler(*pile_fin,casep);
        }
        else if(lettre_ou_chiffre(entree[2])==0){//manger avec ambiguité
            colonne_ou_ligne = adaptateur(entree[1]);
            casep[0]=toupper(entree[3]);
            casep[1]=((int)'9'-(int)entree[4])+48;
            casep[2]='\0';
            if(lettre_ou_chiffre(entree[1])==1){
                for(i=1;i<10;i++){
                    piece_tempo = couleur*100+20+i;
                    if(existence_valeur(piece_tempo,Plateau)){
                        Recherche_piece(tab_position_piece,piece_tempo,Plateau);
                        X=tab_position_piece[0];
                        Y=tab_position_piece[1];
                        liste=Possibilite(Plateau,X,Y,liste,couleur,*pile_depart,*pile_fin,&p_e_p);
                        if(case_dans_liste(liste,casep)){
                            if(X==colonne_ou_ligne){
                                Traducteur(piece_tempo,piece);
                                break;
                            }
                        }
                    }
                }
            }
            else if(lettre_ou_chiffre(entree[1])==-1){
                for(i=1;i<10;i++){
                    piece_tempo = couleur*100+20+i;
                    if(existence_valeur(piece_tempo,Plateau)){
                        Recherche_piece(tab_position_piece,piece_tempo,Plateau);
                        X=tab_position_piece[0];
                        Y=tab_position_piece[1];
                        liste=Possibilite(Plateau,X,Y,liste,couleur,*pile_depart,*pile_fin,&p_e_p);
                        if(case_dans_liste(liste,casep)){
                            if(Y==colonne_ou_ligne){
                                Traducteur(piece_tempo,piece);
                                break;
                            }
                        }
                    }
                }
            }

            Remplacer(Plateau,casep,Coord_to_Nom(X,Y));
            *pile_depart = empiler(*pile_depart,Coord_to_Nom(X,Y));
            *pile_fin = empiler(*pile_fin,casep);
        }
    }
    else if(entree[0]=='N'){
        if(lettre_ou_chiffre(entree[2])==-1 || lettre_ou_chiffre(entree[1])==0){//cavalier déplacement avec manger pas d'ambiguité
            if(lettre_ou_chiffre(entree[1])==1){
                casep[0]=toupper(entree[1]);
                casep[1]=((int)'9'-(int)entree[2])+48;
                casep[2]='\0';
            }
            else if(lettre_ou_chiffre(entree[1])==0){
                casep[0]=toupper(entree[2]);
                casep[1]=((int)'9'-(int)entree[3])+48;
                casep[2]='\0';
            }
            for(i=1;i<10;i++){
                piece_tempo = couleur*100+30+i;
                if(existence_valeur(piece_tempo,Plateau)){
                    Recherche_piece(tab_position_piece,piece_tempo,Plateau);
                    X=tab_position_piece[0];
                    Y=tab_position_piece[1];
                    liste=Possibilite(Plateau,X,Y,liste,couleur,*pile_depart,*pile_fin,&p_e_p);
                    if(case_dans_liste(liste,casep)){
                        Traducteur(piece_tempo,piece);
                        break;
                    }
                }
            }
            Remplacer(Plateau,casep,Coord_to_Nom(X,Y));
            *pile_depart = empiler(*pile_depart,Coord_to_Nom(X,Y));
            *pile_fin = empiler(*pile_fin,casep);
        }
        else if(lettre_ou_chiffre(entree[2])==1){//déplacement ambigue sans manger
            colonne_ou_ligne = adaptateur(entree[1]);
            casep[0]=toupper(entree[2]);
            casep[1]=((int)'9'-(int)entree[3])+48;
            casep[2]='\0';
            if(lettre_ou_chiffre(entree[1])==1){
                for(i=1;i<10;i++){
                    piece_tempo = couleur*100+30+i;
                    if(existence_valeur(piece_tempo,Plateau)){
                        Recherche_piece(tab_position_piece,piece_tempo,Plateau);
                        X=tab_position_piece[0];
                        Y=tab_position_piece[1];
                        liste=Possibilite(Plateau,X,Y,liste,couleur,*pile_depart,*pile_fin,&p_e_p);
                        if(case_dans_liste(liste,casep)){
                            if(X==colonne_ou_ligne){
                                Traducteur(piece_tempo,piece);
                                break;
                            }
                        }
                    }
                }
            }
            else if(lettre_ou_chiffre(entree[1])==-1){
                for(i=1;i<10;i++){
                    piece_tempo = couleur*100+30+i;
                    if(existence_valeur(piece_tempo,Plateau)){
                        Recherche_piece(tab_position_piece,piece_tempo,Plateau);
                        X=tab_position_piece[0];
                        Y=tab_position_piece[1];
                        liste=Possibilite(Plateau,X,Y,liste,couleur,*pile_depart,*pile_fin,&p_e_p);
                        if(case_dans_liste(liste,casep)){
                            if(Y==colonne_ou_ligne){
                                Traducteur(piece_tempo,piece);
                                break;
                            }
                        }
                    }
                }
            }
            Remplacer(Plateau,casep,Coord_to_Nom(X,Y));
            *pile_depart = empiler(*pile_depart,Coord_to_Nom(X,Y));
            *pile_fin = empiler(*pile_fin,casep);
        }
        else if(lettre_ou_chiffre(entree[2])==0){//manger avec ambiguité
            colonne_ou_ligne = adaptateur(entree[1]);
            casep[0]=toupper(entree[3]);
            casep[1]=((int)'9'-(int)entree[4])+48;
            casep[2]='\0';
            if(lettre_ou_chiffre(entree[1])==1){
                for(i=1;i<10;i++){
                    piece_tempo = couleur*100+30+i;
                    if(existence_valeur(piece_tempo,Plateau)){
                        Recherche_piece(tab_position_piece,piece_tempo,Plateau);
                        X=tab_position_piece[0];
                        Y=tab_position_piece[1];
                        liste=Possibilite(Plateau,X,Y,liste,couleur,*pile_depart,*pile_fin,&p_e_p);
                        if(case_dans_liste(liste,casep)){
                            if(X==colonne_ou_ligne){
                                Traducteur(piece_tempo,piece);
                                break;
                            }
                        }
                    }
                }
            }
            else if(lettre_ou_chiffre(entree[1])==-1){
                for(i=1;i<10;i++){
                    piece_tempo = couleur*100+30+i;
                    if(existence_valeur(piece_tempo,Plateau)){
                        Recherche_piece(tab_position_piece,piece_tempo,Plateau);
                        X=tab_position_piece[0];
                        Y=tab_position_piece[1];
                        liste=Possibilite(Plateau,X,Y,liste,couleur,*pile_depart,*pile_fin,&p_e_p);
                        if(case_dans_liste(liste,casep)){
                            if(Y==colonne_ou_ligne){
                                Traducteur(piece_tempo,piece);
                                break;
                            }
                        }
                    }
                }
            }
            Remplacer(Plateau,casep,Coord_to_Nom(X,Y));
            *pile_depart = empiler(*pile_depart,Coord_to_Nom(X,Y));
            *pile_fin = empiler(*pile_fin,casep);
        }
    }
    else if(entree[0]=='B'){
        if(lettre_ou_chiffre(entree[2])==-1 || lettre_ou_chiffre(entree[1])==0){//fou déplacement avec manger pas d'ambiguité
            if(lettre_ou_chiffre(entree[1])==1){
                casep[0]=toupper(entree[1]);
                casep[1]=((int)'9'-(int)entree[2])+48;
                casep[2]='\0';
            }
            else if(lettre_ou_chiffre(entree[1])==0){
                casep[0]=toupper(entree[2]);
                casep[1]=((int)'9'-(int)entree[3])+48;
                casep[2]='\0';
            }
            for(i=1;i<10;i++){
                piece_tempo = couleur*100+40+i;
                if(existence_valeur(piece_tempo,Plateau)){
                    Recherche_piece(tab_position_piece,piece_tempo,Plateau);
                    X=tab_position_piece[0];
                    Y=tab_position_piece[1];
                    liste=Possibilite(Plateau,X,Y,liste,couleur,*pile_depart,*pile_fin,&p_e_p);
                    if(case_dans_liste(liste,casep)){
                        Traducteur(piece_tempo,piece);
                        break;
                    }
                }
            }
            Remplacer(Plateau,casep,Coord_to_Nom(X,Y));
            *pile_depart = empiler(*pile_depart,Coord_to_Nom(X,Y));
            *pile_fin = empiler(*pile_fin,casep);
        }
        else if(lettre_ou_chiffre(entree[2])==1){//déplacement ambigue sans manger
            colonne_ou_ligne = adaptateur(entree[1]);
            casep[0]=toupper(entree[2]);
            casep[1]=((int)'9'-(int)entree[3])+48;
            casep[2]='\0';
            if(lettre_ou_chiffre(entree[1])==1){
                for(i=1;i<10;i++){
                    piece_tempo = couleur*100+40+i;
                    if(existence_valeur(piece_tempo,Plateau)){
                        Recherche_piece(tab_position_piece,piece_tempo,Plateau);
                        X=tab_position_piece[0];
                        Y=tab_position_piece[1];
                        liste=Possibilite(Plateau,X,Y,liste,couleur,*pile_depart,*pile_fin,&p_e_p);
                        if(case_dans_liste(liste,casep)){
                            if(X==colonne_ou_ligne){
                                Traducteur(piece_tempo,piece);
                                break;
                            }
                        }
                    }
                }
            }
            else if(lettre_ou_chiffre(entree[1])==-1){
                for(i=1;i<10;i++){
                    piece_tempo = couleur*100+40+i;
                    if(existence_valeur(piece_tempo,Plateau)){
                        Recherche_piece(tab_position_piece,piece_tempo,Plateau);
                        X=tab_position_piece[0];
                        Y=tab_position_piece[1];
                        liste=Possibilite(Plateau,X,Y,liste,couleur,*pile_depart,*pile_fin,&p_e_p);
                        if(case_dans_liste(liste,casep)){
                            if(Y==colonne_ou_ligne){
                                Traducteur(piece_tempo,piece);
                                break;
                            }
                        }
                    }
                }
            }

            Remplacer(Plateau,casep,Coord_to_Nom(X,Y));
            *pile_depart = empiler(*pile_depart,Coord_to_Nom(X,Y));
            *pile_fin = empiler(*pile_fin,casep);
        }
        else if(lettre_ou_chiffre(entree[2])==0){//manger avec ambiguité
            colonne_ou_ligne = adaptateur(entree[1]);
            casep[0]=toupper(entree[3]);
            casep[1]=((int)'9'-(int)entree[4])+48;
            casep[2]='\0';
            if(lettre_ou_chiffre(entree[1])==1){
                for(i=1;i<10;i++){
                    piece_tempo = couleur*100+40+i;
                    if(existence_valeur(piece_tempo,Plateau)){
                        Recherche_piece(tab_position_piece,piece_tempo,Plateau);
                        X=tab_position_piece[0];
                        Y=tab_position_piece[1];
                        liste=Possibilite(Plateau,X,Y,liste,couleur,*pile_depart,*pile_fin,&p_e_p);
                        if(case_dans_liste(liste,casep)){
                            if(X==colonne_ou_ligne){
                                Traducteur(piece_tempo,piece);
                                break;
                            }
                        }
                    }
                }
            }
            else if(lettre_ou_chiffre(entree[1])==-1){
                for(i=1;i<10;i++){
                    piece_tempo = couleur*100+40+i;
                    if(existence_valeur(piece_tempo,Plateau)){
                        Recherche_piece(tab_position_piece,piece_tempo,Plateau);
                        X=tab_position_piece[0];
                        Y=tab_position_piece[1];
                        liste=Possibilite(Plateau,X,Y,liste,couleur,*pile_depart,*pile_fin,&p_e_p);
                        if(case_dans_liste(liste,casep)){
                            if(Y==colonne_ou_ligne){
                                Traducteur(piece_tempo,piece);
                                break;
                            }
                        }
                    }
                }
            }

            Remplacer(Plateau,casep,Coord_to_Nom(X,Y));
            *pile_depart = empiler(*pile_depart,Coord_to_Nom(X,Y));
            *pile_fin = empiler(*pile_fin,casep);
        }

    }
    else if(entree[0]=='Q'){
        if(lettre_ou_chiffre(entree[2])==-1 || lettre_ou_chiffre(entree[1])==0){//fou déplacement avec manger pas d'ambiguité
            if(lettre_ou_chiffre(entree[1])==1){
                casep[0]=toupper(entree[1]);
                casep[1]=((int)'9'-(int)entree[2])+48;
                casep[2]='\0';
            }
            else if(lettre_ou_chiffre(entree[1])==0){
                casep[0]=toupper(entree[2]);
                casep[1]=((int)'9'-(int)entree[3])+48;
                casep[2]='\0';
            }
            for(i=1;i<10;i++){
                piece_tempo = couleur*100+50+i;
                if(existence_valeur(piece_tempo,Plateau)){
                    Recherche_piece(tab_position_piece,piece_tempo,Plateau);
                    X=tab_position_piece[0];
                    Y=tab_position_piece[1];
                    liste=Possibilite(Plateau,X,Y,liste,couleur,*pile_depart,*pile_fin,&p_e_p);
                    if(case_dans_liste(liste,casep)){
                        Traducteur(piece_tempo,piece);
                        break;
                    }
                }
            }
            Remplacer(Plateau,casep,Coord_to_Nom(X,Y));
            *pile_depart = empiler(*pile_depart,Coord_to_Nom(X,Y));
            *pile_fin = empiler(*pile_fin,casep);
        }
        else if(lettre_ou_chiffre(entree[2])==1){//déplacement ambigue sans manger
            colonne_ou_ligne = adaptateur(entree[1]);
            casep[0]=toupper(entree[2]);
            casep[1]=((int)'9'-(int)entree[3])+48;
            casep[2]='\0';
            if(lettre_ou_chiffre(entree[1])==1){
                for(i=1;i<10;i++){
                    piece_tempo = couleur*100+50+i;
                    if(existence_valeur(piece_tempo,Plateau)){
                        Recherche_piece(tab_position_piece,piece_tempo,Plateau);
                        X=tab_position_piece[0];
                        Y=tab_position_piece[1];
                        liste=Possibilite(Plateau,X,Y,liste,couleur,*pile_depart,*pile_fin,&p_e_p);
                        if(case_dans_liste(liste,casep)){
                            if(X==colonne_ou_ligne){
                                Traducteur(piece_tempo,piece);
                                break;
                            }
                        }
                    }
                }
            }
            else if(lettre_ou_chiffre(entree[1])==-1){
                for(i=1;i<10;i++){
                    piece_tempo = couleur*100+50+i;
                    if(existence_valeur(piece_tempo,Plateau)){
                        Recherche_piece(tab_position_piece,piece_tempo,Plateau);
                        X=tab_position_piece[0];
                        Y=tab_position_piece[1];
                        liste=Possibilite(Plateau,X,Y,liste,couleur,*pile_depart,*pile_fin,&p_e_p);
                        if(case_dans_liste(liste,casep)){
                            if(Y==colonne_ou_ligne){
                                Traducteur(piece_tempo,piece);
                                break;
                            }
                        }
                    }
                }
            }

            Remplacer(Plateau,casep,Coord_to_Nom(X,Y));
            *pile_depart = empiler(*pile_depart,Coord_to_Nom(X,Y));
            *pile_fin = empiler(*pile_fin,casep);
        }
        else if(lettre_ou_chiffre(entree[2])==0){//manger avec ambiguité
            colonne_ou_ligne = adaptateur(entree[1]);
            casep[0]=toupper(entree[3]);
            casep[1]=((int)'9'-(int)entree[4])+48;
            casep[2]='\0';
            if(lettre_ou_chiffre(entree[1])==1){
                for(i=1;i<10;i++){
                    piece_tempo = couleur*100+50+i;
                    if(existence_valeur(piece_tempo,Plateau)){
                        Recherche_piece(tab_position_piece,piece_tempo,Plateau);
                        X=tab_position_piece[0];
                        Y=tab_position_piece[1];
                        liste=Possibilite(Plateau,X,Y,liste,couleur,*pile_depart,*pile_fin,&p_e_p);
                        if(case_dans_liste(liste,casep)){
                            if(X==colonne_ou_ligne){
                                Traducteur(piece_tempo,piece);
                                break;
                            }
                        }
                    }
                }
            }
            else if(lettre_ou_chiffre(entree[1])==-1){
                for(i=1;i<10;i++){
                    piece_tempo = couleur*100+50+i;
                    if(existence_valeur(piece_tempo,Plateau)){
                        Recherche_piece(tab_position_piece,piece_tempo,Plateau);
                        X=tab_position_piece[0];
                        Y=tab_position_piece[1];
                        liste=Possibilite(Plateau,X,Y,liste,couleur,*pile_depart,*pile_fin,&p_e_p);
                        if(case_dans_liste(liste,casep)){
                            if(Y==colonne_ou_ligne){
                                Traducteur(piece_tempo,piece);
                                break;
                            }
                        }
                    }
                }
            }

            Remplacer(Plateau,casep,Coord_to_Nom(X,Y));
            *pile_depart = empiler(*pile_depart,Coord_to_Nom(X,Y));
            *pile_fin = empiler(*pile_fin,casep);
        }
    }
    else if(entree[0]=='K'){
        if(lettre_ou_chiffre(entree[2])==-1 || lettre_ou_chiffre(entree[1])==0){//fou déplacement avec manger pas d'ambiguité
            if(lettre_ou_chiffre(entree[1])==1){
                casep[0]=toupper(entree[1]);
                casep[1]=((int)'9'-(int)entree[2])+48;
                casep[2]='\0';
            }
            else if(lettre_ou_chiffre(entree[1])==0){
                casep[0]=toupper(entree[2]);
                casep[1]=((int)'9'-(int)entree[3])+48;
                casep[2]='\0';
            }
            piece_tempo = couleur*100+61;
            if(existence_valeur(piece_tempo,Plateau)){
                Recherche_piece(tab_position_piece,piece_tempo,Plateau);
                X=tab_position_piece[0];
                Y=tab_position_piece[1];
                Traducteur(piece_tempo,piece);
            }

        }
        Remplacer(Plateau,casep,Coord_to_Nom(X,Y));
        *pile_depart = empiler(*pile_depart,Coord_to_Nom(X,Y));
        *pile_fin = empiler(*pile_fin,casep);
    }
    else if(entree[0]=='O'){
        if(strcmp(entree,"O-O-O")==0){
            if(couleur==1){
                Remplacer(Plateau,"C8","E8");
                Remplacer(Plateau,"D8","A8");
                strcpy(casep,"0");
                strcpy(piece,"g");
                *pile_depart = empiler(*pile_depart,"A8");
                *pile_fin = empiler(*pile_fin,"D8");
            }
            else{
                Remplacer(Plateau,"C1","E1");
                Remplacer(Plateau,"D1","18");
                strcpy(casep,"0");
                strcpy(piece,"g");
                *pile_depart = empiler(*pile_depart,"A1");
                *pile_fin = empiler(*pile_fin,"D1");
            }
        }
        else{
            if(couleur==1){
                Remplacer(Plateau,"G8","E8");
                Remplacer(Plateau,"F8","H8");
                strcpy(casep,"0");
                strcpy(piece,"p");
                *pile_depart = empiler(*pile_depart,"H8");
                *pile_fin = empiler(*pile_fin,"F8");
            }
            else{
                Remplacer(Plateau,"G1","E1");
                Remplacer(Plateau,"F1","H1");
                strcpy(casep,"0");
                strcpy(piece,"p");
                *pile_depart = empiler(*pile_depart,"H1");
                *pile_fin = empiler(*pile_fin,"F1");
            }
        }
    }

}
int adaptateur(char lettre){
    int result;
    if(lettre_ou_chiffre(lettre)==1){
        result = (int)lettre-97;
    }
    else if(lettre_ou_chiffre(lettre)==-1){
        result = 56-(int)lettre;
    }

    return result;


}
void Changement_Pion_ia(int Plateau[][8],char sup){

    if(sup!='0'){
        int i,ligne,colonne,N,T;
    /*fonction pour l'ia qui ne met pas de scanf car c'est l'ordi qui joue mais toujour le même règle*/

        for(ligne=0; ligne<8;ligne+=7){// Colonne 1 et 8 cf:Affichage
            for(colonne=0;colonne<8;colonne++){

                if((int)(Plateau[ligne][colonne]-100*((int)Plateau[ligne][colonne]/100))/10 == 1 ){//si le numero Type piece = Pions

                    int C = (int)Plateau[ligne][colonne]/100; //Couleur

                    switch (sup){
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
                }
            }
        }
    }
}
int lettre_ou_chiffre(char caractere){/*détermine si un caractère est un chiffre compris entre 1 et 8 ou une lettre compris entre 'a' et 'h' ou un 'x'*/
    int result;//1--> lettre, -1-->chiffre, autre-->0
    if((int)caractere<105 && (int)caractere>96){
        result=1;
    }
    else if((int)caractere<57 && (int)caractere>48){
        result=-1;
    }
    else if((int)caractere ==120){
        result =0;
    }
    else if(caractere=='N'|| caractere=='K'|| caractere=='Q'|| caractere=='R'|| caractere=='B'){
        result=2;
    }
    else{
        result=-2;
    }
    return result;


}
void ecriture(char *temp,int *i,char *chaine){/*sous fonction d'affinnage base de données*/
    int l=0;
    *i =*i+ 1;

    while(chaine[*i]!=' ' && chaine[*i]!='\n'){
        temp[l]=chaine[*i];
        *i =*i+ 1;
        l++;
    }
    if(chaine[*i]=='\n'){
       *i=*i-1;
    }
    temp[l]='\0';



}
void affinage_base_de_donnees(){
    /*fonction qui affine une base de données de parties c'est un peu du bidoullage car
    la base de données a ses propres coquilles*/
    FILE *f=fopen("test.txt","r");
    FILE *f1=fopen("transfo.txt","a");
    char chaine[2500];
    char temp[10];
    while(fgets(chaine,2500,f)!=NULL){
        int i=0;
        while(chaine[i]!='\n'){
            if(chaine[i]=='.' && chaine[i+1]!=' '){
                ecriture(temp,&i,chaine);
                fprintf(f1,"%s ",temp);
                if(((int)chaine[i+1]<48 || (int)chaine[i+1]>57) && chaine[i+1]!='$' && chaine[i]!='\n'){
                    ecriture(temp,&i,chaine);
                    fprintf(f1,"%s ",temp);

                }
                else if(chaine[i+1]=='$' && chaine[i+3]!='\n'){
                    i=i+3;
                    ecriture(temp,&i,chaine);
                    fprintf(f1,"%s ",temp);
                }

            }
            else if(chaine[i]=='.' && chaine[i+1]==' '){
                i++;
                ecriture(temp,&i,chaine);
                fprintf(f1,"%s ",temp);
                if(((int)chaine[i+1]<48 || (int)chaine[i+1]>57) && chaine[i+1]!='$' && chaine[i]!='\n'){
                    ecriture(temp,&i,chaine);
                    fprintf(f1,"%s ",temp);
                }
                else if(chaine[i+1]=='$' && chaine[i+3]!='\n'){
                    i=i+3;
                    ecriture(temp,&i,chaine);
                    fprintf(f1,"%s ",temp);
                }

            }
            i++;


        }
        fprintf(f1,"\n");
    }
    fclose(f);
    fclose(f1);


}
void piece_et_case_aleatoire(char *casep,char *piece,int Plateau[][8],int couleur){
    int abs_rd,ord_rd,piece_value,p_e_p=0;

    Liste_possibilitees *liste=NULL;
    srand(time(NULL));
    do{
        abs_rd=rand()%8;
        ord_rd=rand()%8;
        piece_value=Plateau[ord_rd][abs_rd];
        if((int)piece_value/100==couleur){
            liste = Possibilite(Plateau,abs_rd,ord_rd,liste,couleur,NULL,NULL,&p_e_p);
        }

    }while((int)piece_value/100!=couleur || liste==NULL);
    Traducteur(piece_value,piece);
    strcpy(casep,Coord_to_Nom(liste->abscisse,liste->ordonnee));





}



