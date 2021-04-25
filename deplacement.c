#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "outil.h"
#include "liste.h"
#include "pile.h"
#include "deplacement.h"


int test_echec(int Plateau[][8],int couleur){/*fonction qui prend en entree la couleur du joueur qui doit jouer et retourne 1 si le roi de cette couleur
    est en echec 0 sinon*/
    int abscisse_roi,ordonnee_roi,i,j,echec=0,val_roi,couleur_adverse;
    int tab_tempo[2];
    Liste_possibilitees *liste=NULL;
    val_roi = 100*couleur + 61;
    Recherche_piece(tab_tempo,val_roi,Plateau);
    abscisse_roi =tab_tempo[0];
    ordonnee_roi =tab_tempo[1];
    if(couleur==1){
        couleur_adverse=2;
    }
    else{
        couleur_adverse=1;
    }
    for(i=0;i<8;i++){
        for(j=0;j<8;j++){
            if((int)Plateau[i][j]/100 ==couleur_adverse){
                liste=Possibilite_modifie(Plateau,j,i,liste);/*ici très important détail, on utilise la fonction Possibilite_modifie et non Posibilite
                                                               pourquoi? Car dans Possibilite on utilise la fonction test_echec ce qui impliquerait une boucle
                                                               = plantage */
                while(liste !=NULL){
                    if(liste->abscisse == abscisse_roi && liste->ordonnee == ordonnee_roi){
                        echec = 1;
                    }
                    liste=liste->suivant;
                }
            }
        }
    }
    return echec;
}

Liste_possibilitees *Possibilite_modifie(int Plateau[][8] ,int X ,int Y,Liste_possibilitees *liste){
    /*fonction qui remplit une liste chaîne de cases possibles pour une pièce entrée
    attention cette fonction n'est pas sensible au clouement d'une pièce, c'est à dire qu'elle donne les possibilitées brutes
    d'une pièce
    */
    int piece = Plateau[Y][X];
    int tab_coordonnees[50][2]={0};
    int nb_case,i,j;
    int C = (int)piece/100; //Couleur
    int T = (int)(piece-100*C)/10; //Type
    int e_p=0;


    switch (T){
        case 1 :// Pion

            //Influence de la couleur sur le Deplacement
            nb_case=0;
            remplissage_cases_pion(tab_coordonnees,&nb_case,X,Y,C,Plateau,&e_p,NULL,NULL);

            for(i=0;i<nb_case;i++)
            {
                liste =insertion(liste,tab_coordonnees[i][0],tab_coordonnees[i][1]);
            }


            break;

        case 2: //Tours
            nb_case=0;
            j=0;
            remplissage_cases_tour(tab_coordonnees,&nb_case,X,Y,C,Plateau,&j);
            for(i=0;i<nb_case;i++)
            {
                liste = insertion(liste,tab_coordonnees[i][0],tab_coordonnees[i][1]);
            }

            break;
        case 3: //Cavalier
            nb_case=0;
            remplissage_cases_cavalier(tab_coordonnees,&nb_case,X,Y,C,Plateau);
            for(i=0;i<nb_case;i++)
            {
                liste = insertion(liste,tab_coordonnees[i][0],tab_coordonnees[i][1]);
            }

            break;
        case 4: //Fou
            nb_case=0;
            j=0;
            remplissage_cases_fou(tab_coordonnees,&nb_case,X,Y,C,Plateau,j);
            for(i=0;i<nb_case;i++)
            {
                liste = insertion(liste,tab_coordonnees[i][0],tab_coordonnees[i][1]);
            }

            break;
        case 5: //Dame
            nb_case=0;
            j=0;
            remplissage_cases_tour(tab_coordonnees,&nb_case,X,Y,C,Plateau,&j);
            remplissage_cases_fou(tab_coordonnees,&nb_case,X,Y,C,Plateau,j);

            for(i=0;i<nb_case;i++)
            {
                liste = insertion(liste,tab_coordonnees[i][0],tab_coordonnees[i][1]);
            }

            break;
        case 6: //Roi
            nb_case=0;
            remplissage_cases_roi(tab_coordonnees,&nb_case,X,Y,C,Plateau);

            for(i=0;i<nb_case;i++)
            {
                liste = insertion(liste,tab_coordonnees[i][0],tab_coordonnees[i][1]);
            }


            break;
    }
    return liste;

}
Liste_possibilitees *Possibilite(int Plateau[][8] ,int X ,int Y,Liste_possibilitees *liste,int couleur,Pile *pile_depart,Pile *pile_fin,int *p_e_p){
    /*fonction qui calcule et remplit les possibilités d'une piece dans une liste,
    cette fonction est sensible au clouement c'est à dire qu'on supprime les possibilités
    qui sont hors la loi */


    int piece = Plateau[Y][X];
    int tab_coordonnees[50][2]={0};
    int nb_case,i,j;
    Liste_possibilitees *transfert=NULL;
    int val_remplacement=0;
    int e_p=0;
    int indice=0;
    int C = (int)piece/100; //Couleur
    int T = (int)(piece-100*C)/10; //Type

    switch (T){
        case 1 :// Pion

            //Influence de la couleur sur le Deplacement
            nb_case=0;
            int piece_prise_en_passant;
            remplissage_cases_pion(tab_coordonnees,&nb_case,X,Y,C,Plateau,&e_p,pile_depart,pile_fin);
            *p_e_p =e_p; /*e_p est modifié dans remplissage cases_pions si il y a une prise en passant
                            il peut prendre trois valeurs, 1 si on fait une prise en passant vers la droite
                            -1 pour la gauche et 0 si pas de prise en passant*/
            //printf("%d",e_p);
            for(i=0;i<nb_case;i++)
            {
                liste =insertion(liste,tab_coordonnees[i][0],tab_coordonnees[i][1]);
            }
            transfert = liste;
            while(transfert!=NULL){
                if(e_p==0){
                    /*ici ce qu'on fait c'est que l'on teste chaque possibilité c'est à dire qu'on change la position
                    de la piéce entrée dans toutes ses possibilités et on regarde avec la fonction test echec si on
                    est en échec aprés le changement de position si oui, on supprime la possibilité car on ne
                    peut pas se mettre en échec soit même aux échecs*/

                    Remplacer_abs_ord(Plateau,X,Y,transfert->abscisse,transfert->ordonnee,&val_remplacement);//on remplace une fois
                    if(test_echec(Plateau,couleur)==1){
                        liste =suppression(liste,transfert);
                    }
                    Remplacer_abs_ord(Plateau,transfert->abscisse,transfert->ordonnee,X,Y,&val_remplacement);/*puis une deuxieme pour revenir à l'état initial
                                                                                                                au final on ne change rien du plateau*/
                }
                else if(e_p==1){
                    if(indice<1){
                        piece_prise_en_passant = Plateau[Y][X+1];
                        Plateau[Y][X+1]=0;
                        Remplacer(Plateau,Coord_to_Nom(transfert->abscisse,transfert->ordonnee),Coord_to_Nom(X,Y));
                        if(test_echec(Plateau,couleur)==1){
                            liste =suppression(liste,transfert);
                        }
                        Plateau[Y][X+1]=piece_prise_en_passant;
                        Remplacer(Plateau,Coord_to_Nom(X,Y),Coord_to_Nom(transfert->abscisse,transfert->ordonnee));

                        indice++;
                    }
                    else{
                        Remplacer_abs_ord(Plateau,X,Y,transfert->abscisse,transfert->ordonnee,&val_remplacement);
                        if(test_echec(Plateau,couleur)==1){
                            liste =suppression(liste,transfert);
                        }
                        Remplacer_abs_ord(Plateau,transfert->abscisse,transfert->ordonnee,X,Y,&val_remplacement);
                    }



                }
                else{
                    if(indice<1){
                        piece_prise_en_passant = Plateau[Y][X-1];
                        Plateau[Y][X-1]=0;
                        Remplacer(Plateau,Coord_to_Nom(transfert->abscisse,transfert->ordonnee),Coord_to_Nom(X,Y));
                        if(test_echec(Plateau,couleur)==1){
                            liste =suppression(liste,transfert);
                        }
                        Plateau[Y][X-1]=piece_prise_en_passant;
                        Remplacer(Plateau,Coord_to_Nom(X,Y),Coord_to_Nom(transfert->abscisse,transfert->ordonnee));

                        indice++;
                    }
                    else{
                        Remplacer_abs_ord(Plateau,X,Y,transfert->abscisse,transfert->ordonnee,&val_remplacement);
                        if(test_echec(Plateau,couleur)==1){
                            liste =suppression(liste,transfert);
                        }
                        Remplacer_abs_ord(Plateau,transfert->abscisse,transfert->ordonnee,X,Y,&val_remplacement);
                    }
                }
                transfert=transfert->suivant;
                val_remplacement=0;


            }


            break;

        case 2: //Tours
            nb_case=0;
            j=0;
            remplissage_cases_tour(tab_coordonnees,&nb_case,X,Y,C,Plateau,&j);
            for(i=0;i<nb_case;i++)
            {
                liste = insertion(liste,tab_coordonnees[i][0],tab_coordonnees[i][1]);
            }
            transfert = liste;
            while(transfert!=NULL){
                Remplacer_abs_ord(Plateau,X,Y,transfert->abscisse,transfert->ordonnee,&val_remplacement);
                if(test_echec(Plateau,couleur)==1){

                    liste=suppression(liste,transfert);
                }
                Remplacer_abs_ord(Plateau,transfert->abscisse,transfert->ordonnee,X,Y,&val_remplacement);
                transfert=transfert->suivant;
                val_remplacement=0;
            }
            break;
        case 3: //Cavalier
            nb_case=0;
            remplissage_cases_cavalier(tab_coordonnees,&nb_case,X,Y,C,Plateau);
            for(i=0;i<nb_case;i++)
            {
                liste = insertion(liste,tab_coordonnees[i][0],tab_coordonnees[i][1]);
            }
            transfert = liste;
            while(transfert!=NULL){
                Remplacer_abs_ord(Plateau,X,Y,transfert->abscisse,transfert->ordonnee,&val_remplacement);
                if(test_echec(Plateau,couleur)==1){
                    liste=suppression(liste,transfert);
                }
                Remplacer_abs_ord(Plateau,transfert->abscisse,transfert->ordonnee,X,Y,&val_remplacement);
                transfert=transfert->suivant;
                val_remplacement=0;
            }
            break;
        case 4: //Fou
            nb_case=0;
            j=0;
            remplissage_cases_fou(tab_coordonnees,&nb_case,X,Y,C,Plateau,j);
            for(i=0;i<nb_case;i++)
            {
                liste = insertion(liste,tab_coordonnees[i][0],tab_coordonnees[i][1]);
            }
            transfert = liste;
            while(transfert!=NULL){
                Remplacer_abs_ord(Plateau,X,Y,transfert->abscisse,transfert->ordonnee,&val_remplacement);
                if(test_echec(Plateau,couleur)==1){
                    liste=suppression(liste,transfert);
                }
                Remplacer_abs_ord(Plateau,transfert->abscisse,transfert->ordonnee,X,Y,&val_remplacement);
                transfert=transfert->suivant;
                val_remplacement=0;
            }
            break;
        case 5: //Dame
            nb_case=0;
            j=0;
            remplissage_cases_tour(tab_coordonnees,&nb_case,X,Y,C,Plateau,&j);
            remplissage_cases_fou(tab_coordonnees,&nb_case,X,Y,C,Plateau,j);

            for(i=0;i<nb_case;i++)
            {
                liste = insertion(liste,tab_coordonnees[i][0],tab_coordonnees[i][1]);
            }
            transfert = liste;
            while(transfert!=NULL){
                Remplacer_abs_ord(Plateau,X,Y,transfert->abscisse,transfert->ordonnee,&val_remplacement);
                if(test_echec(Plateau,couleur)==1){
                    liste=suppression(liste,transfert);
                }
                Remplacer_abs_ord(Plateau,transfert->abscisse,transfert->ordonnee,X,Y,&val_remplacement);
                transfert=transfert->suivant;
                val_remplacement=0;
            }
            break;
        case 6: //Roi
            nb_case=0;
            remplissage_cases_roi(tab_coordonnees,&nb_case,X,Y,C,Plateau);

            for(i=0;i<nb_case;i++)
            {
                liste = insertion(liste,tab_coordonnees[i][0],tab_coordonnees[i][1]);
            }
            transfert = liste;
            while(transfert!=NULL){
                Remplacer_abs_ord(Plateau,X,Y,transfert->abscisse,transfert->ordonnee,&val_remplacement);
                if(test_echec(Plateau,couleur)==1){
                    liste=suppression(liste,transfert);
                }
                Remplacer_abs_ord(Plateau,transfert->abscisse,transfert->ordonnee,X,Y,&val_remplacement);
                transfert=transfert->suivant;
                val_remplacement=0;
            }

            break;
    }
    return liste;



}

void remplissage_cases_pion(int tab_coordonnees[][2],int *nb_case,int abscisse,int ordonnee,int couleur,int Plateau[][8],int *e_p,Pile *depart_case,Pile *fin_case){
    /*remplit un tableau de coordonnees a deux dimensions qui sert d'intermediaire avant de remplir la liste,
    on le remplit de la maniere [[x1,y1],
                                 [x2,y2]]
    chaque ligne est une position possible du pion */
    /*modification de la fonction pour la prise en passant ajout en entrée de deux piles et d'un pointeur indicateur d'une prise
    en passant ou non, les deux piles , pourquoi? et bien la prise en passant ne peut s'effectuer que le tour suivant le
    déplacement du pion adverse donc les piles enregistrent à chaque mouvement la case de départ et la case d'arrivée c'est
    essentiel pour conserver la condition qui est de faire la prise en passant juste après le déplacement du pion et pas deux tours après
    si toutes le conditions sont réunis on ajoute au tableau de nouvelles possibilités pour le pion*/

    int j=0;
    if(couleur == 2)
    {
        if(Plateau[ordonnee+1][abscisse]==0)
        {
            tab_coordonnees[j][0]=abscisse;
            tab_coordonnees[j][1]=ordonnee+1;
            j++;
            *nb_case+=1;
        }
        if(Plateau[ordonnee+2][abscisse]==0 && ordonnee==1 && Plateau[ordonnee+1][abscisse]==0)
        {
            tab_coordonnees[j][0]=abscisse;
            tab_coordonnees[j][1]=ordonnee+2;
            j++;
            *nb_case+=1;
        }
        if((int)Plateau[ordonnee+1][abscisse-1]/100 ==1 && abscisse !=0)
        {
            tab_coordonnees[j][0]=abscisse-1;
            tab_coordonnees[j][1]=ordonnee+1;
            j++;
            *nb_case+=1;
        }
        if((int)Plateau[ordonnee+1][abscisse+1]/100 ==1 && abscisse !=7)
        {
            tab_coordonnees[j][0]=abscisse+1;
            tab_coordonnees[j][1]=ordonnee+1;
            j++;
            *nb_case+=1;
        }
        if(ordonnee==4){
            char case_haut_de_pile_depart[5];
            char case_haut_de_pile_fin[5];
            if(fin_case!=NULL && depart_case!=NULL){
                strcpy(case_haut_de_pile_depart,fin_case->casep);
                strcpy(case_haut_de_pile_fin,depart_case->casep);
                if(abscisse == 7){
                    if(strcmp(case_haut_de_pile_depart,Coord_to_Nom(abscisse-1,ordonnee))==0){
                        if(strcmp(case_haut_de_pile_fin,Coord_to_Nom(abscisse-1,ordonnee+2))==0){
                            if(((int)(Plateau[ordonnee][abscisse-1]-100)/10)==1){
                                tab_coordonnees[j][0]=abscisse-1;
                                tab_coordonnees[j][1]=ordonnee+1;
                                j++;
                                *nb_case+=1;
                                *e_p =-1;
                            }
                        }
                    }
                }
                else if(abscisse==0){
                    if(strcmp(case_haut_de_pile_depart,Coord_to_Nom(abscisse+1,ordonnee))==0){
                        if(strcmp(case_haut_de_pile_fin,Coord_to_Nom(abscisse+1,ordonnee+2))==0){
                            if(((int)(Plateau[ordonnee][abscisse+1]-100)/10)==1){
                                tab_coordonnees[j][0]=abscisse+1;
                                tab_coordonnees[j][1]=ordonnee+1;
                                j++;
                                *nb_case+=1;
                                *e_p =1;
                            }
                        }
                    }
                }
                else{
                    if(strcmp(case_haut_de_pile_depart,Coord_to_Nom(abscisse+1,ordonnee))==0){
                        if(strcmp(case_haut_de_pile_fin,Coord_to_Nom(abscisse+1,ordonnee+2))==0){
                            if(((int)(Plateau[ordonnee][abscisse+1]-100)/10)==1){
                                tab_coordonnees[j][0]=abscisse+1;
                                tab_coordonnees[j][1]=ordonnee+1;
                                j++;
                                *nb_case+=1;
                                *e_p =1;
                            }
                        }
                    }
                    else if(strcmp(case_haut_de_pile_depart,Coord_to_Nom(abscisse-1,ordonnee))==0){
                        if(strcmp(case_haut_de_pile_fin,Coord_to_Nom(abscisse-1,ordonnee+2))==0){
                            if(((int)(Plateau[ordonnee][abscisse-1]-100)/10)==1){
                                tab_coordonnees[j][0]=abscisse-1;
                                tab_coordonnees[j][1]=ordonnee+1;
                                j++;
                                *nb_case+=1;
                                *e_p =-1;
                            }
                        }
                    }
                }
            }
        }
    }
    else if(couleur==1)
    {
        if(Plateau[ordonnee-1][abscisse]==0)
        {
            tab_coordonnees[j][0]=abscisse;
            tab_coordonnees[j][1]=ordonnee-1;
            j++;
            *nb_case+=1;
        }
        if(Plateau[ordonnee-2][abscisse]==0 && ordonnee==6 && Plateau[ordonnee-1][abscisse]==0)
        {
            tab_coordonnees[j][0]=abscisse;
            tab_coordonnees[j][1]=ordonnee-2;
            j++;
            *nb_case+=1;
        }
        if((int)Plateau[ordonnee-1][abscisse-1]/100 ==2 && abscisse !=0)
        {
            tab_coordonnees[j][0]=abscisse-1;
            tab_coordonnees[j][1]=ordonnee-1;
            j++;
            *nb_case+=1;
        }
        if((int)Plateau[ordonnee-1][abscisse+1]/100 ==2 && abscisse !=7)
        {
            tab_coordonnees[j][0]=abscisse+1;
            tab_coordonnees[j][1]=ordonnee-1;
            j++;
            *nb_case+=1;
        }
        if(ordonnee==3){
            char case_haut_de_pile_depart[5];
            char case_haut_de_pile_fin[5];

            if(fin_case!=NULL && depart_case!=NULL){
                strcpy(case_haut_de_pile_depart,fin_case->casep);
                strcpy(case_haut_de_pile_fin,depart_case->casep);
                if(abscisse == 7){
                    if(strcmp(case_haut_de_pile_depart,Coord_to_Nom(abscisse-1,ordonnee))==0){
                        if(strcmp(case_haut_de_pile_fin,Coord_to_Nom(abscisse-1,ordonnee-2))==0){
                            if(((int)(Plateau[ordonnee][abscisse-1]-200)/10)==1){
                                tab_coordonnees[j][0]=abscisse-1;
                                tab_coordonnees[j][1]=ordonnee-1;
                                j++;
                                *nb_case+=1;
                                *e_p =-1;
                            }
                        }
                    }
                }
                else if(abscisse==0){
                    if(strcmp(case_haut_de_pile_depart,Coord_to_Nom(abscisse+1,ordonnee))==0){
                        if(strcmp(case_haut_de_pile_fin,Coord_to_Nom(abscisse+1,ordonnee-2))==0){
                            if(((int)(Plateau[ordonnee][abscisse+1]-200)/10)==1){
                                tab_coordonnees[j][0]=abscisse+1;
                                tab_coordonnees[j][1]=ordonnee-1;
                                j++;
                                *nb_case+=1;
                                *e_p =1;
                            }
                        }
                    }
                }
                else{
                    if(strcmp(case_haut_de_pile_depart,Coord_to_Nom(abscisse+1,ordonnee))==0){
                        if(strcmp(case_haut_de_pile_fin,Coord_to_Nom(abscisse+1,ordonnee-2))==0){
                            if(((int)(Plateau[ordonnee][abscisse+1]-200)/10)==1){
                                tab_coordonnees[j][0]=abscisse+1;
                                tab_coordonnees[j][1]=ordonnee-1;
                                j++;
                                *nb_case+=1;
                                *e_p =1;
                            }
                        }
                    }
                    else if(strcmp(case_haut_de_pile_depart,Coord_to_Nom(abscisse-1,ordonnee))==0){
                        if(strcmp(case_haut_de_pile_fin,Coord_to_Nom(abscisse-1,ordonnee-2))==0){
                            if(((int)(Plateau[ordonnee][abscisse-1]-200)/10)==1){
                                tab_coordonnees[j][0]=abscisse-1;
                                tab_coordonnees[j][1]=ordonnee-1;
                                j++;
                                *nb_case+=1;
                                *e_p =-1;
                            }
                        }
                    }
                }
            }
        }
    }
}

void remplissage_cases_tour(int tab_coordonnees[][2],int *nb_case,int abscisse,int ordonnee,int couleur,int Plateau[][8],int *j){
    /*idem que remplissage pions*/
    int i,arret_haut=1,arret_bas=1,arret_droit=1,arret_gauche=1;
    for(i=1;i<8;i++)
    {
        if(arret_haut)
        {
            if(ordonnee-i >=0)
            {
                if(Plateau[ordonnee-i][abscisse]==0)
                {
                    tab_coordonnees[*j][0] = abscisse;
                    tab_coordonnees[*j][1] = ordonnee-i;
                    *j+=1;
                    *nb_case+=1;
                }
                else if((int)Plateau[ordonnee-i][abscisse]/100==couleur)
                {
                    arret_haut=0;
                }
                else if((int)Plateau[ordonnee-i][abscisse]/100!=couleur)
                {
                    tab_coordonnees[*j][0] = abscisse;
                    tab_coordonnees[*j][1] = ordonnee-i;
                    *j+=1;
                    *nb_case+=1;
                    arret_haut=0;
                }
            }
        }
        if(arret_bas)
        {
            if(ordonnee+i <=7)
            {
                if(Plateau[ordonnee+i][abscisse]==0)
                {
                    tab_coordonnees[*j][0] = abscisse;
                    tab_coordonnees[*j][1] = ordonnee+i;
                    *j+=1;
                    *nb_case+=1;
                }
                else if((int)Plateau[ordonnee+i][abscisse]/100==couleur)
                {
                    arret_bas=0;
                }
                else if((int)Plateau[ordonnee+i][abscisse]/100!=couleur)
                {
                    tab_coordonnees[*j][0] = abscisse;
                    tab_coordonnees[*j][1] = ordonnee+i;
                    *j+=1;
                    *nb_case+=1;
                    arret_bas=0;
                }
            }
        }
        if(arret_droit)
        {
            if(abscisse+i <=7)
            {
                if(Plateau[ordonnee][abscisse+i]==0)
                {
                    tab_coordonnees[*j][0] = abscisse+i;
                    tab_coordonnees[*j][1] = ordonnee;
                    *j+=1;
                    *nb_case+=1;
                }
                else if((int)Plateau[ordonnee][abscisse+i]/100==couleur)
                {
                    arret_droit=0;
                }
                else if((int)Plateau[ordonnee][abscisse+i]/100!=couleur)
                {
                    tab_coordonnees[*j][0] = abscisse+i;
                    tab_coordonnees[*j][1] = ordonnee;
                    *j+=1;
                    *nb_case+=1;
                    arret_droit=0;
                }
            }
        }
        if(arret_gauche)
        {
            if(abscisse-i >=0)
            {
                if(Plateau[ordonnee][abscisse-i]==0)
                {
                    tab_coordonnees[*j][0] = abscisse-i;
                    tab_coordonnees[*j][1] = ordonnee;
                    *j+=1;
                    *nb_case+=1;
                }
                else if((int)Plateau[ordonnee][abscisse-i]/100==couleur)
                {
                    arret_gauche=0;
                }
                else if((int)Plateau[ordonnee][abscisse-i]/100!=couleur)
                {
                    tab_coordonnees[*j][0] = abscisse-i;
                    tab_coordonnees[*j][1] = ordonnee;
                    *j+=1;
                    *nb_case+=1;
                    arret_gauche=0;
                }
            }
        }

    }


}

void remplissage_cases_cavalier(int tab_coordonnees[][2],int *nb_case,int abscisse,int ordonnee,int couleur,int Plateau[][8]){
    int j=0,i;
    for(i=0;i<8;i++)
    {
        switch(i)
        {
            case 0:
                if(abscisse+2<=7 && ordonnee-1>=0)
                {
                    if(Plateau[ordonnee-1][abscisse+2]==0 || (int)Plateau[ordonnee-1][abscisse+2]/100 !=couleur)
                    {
                        tab_coordonnees[j][0]=abscisse+2;
                        tab_coordonnees[j][1]=ordonnee-1;
                        *nb_case+=1;
                        j++;
                    }
                }
                break;
            case 1:
                if(abscisse+1<=7 && ordonnee-2>=0)
                {
                    if(Plateau[ordonnee-2][abscisse+1]==0 || (int)Plateau[ordonnee-2][abscisse+1]/100 !=couleur)
                    {
                        tab_coordonnees[j][0]=abscisse+1;
                        tab_coordonnees[j][1]=ordonnee-2;
                        *nb_case+=1;
                        j++;
                    }
                }
                break;
            case 2:
                if(abscisse-1>=0 && ordonnee-2>=0)
                {
                    if(Plateau[ordonnee-2][abscisse-1]==0 || (int)Plateau[ordonnee-2][abscisse-1]/100 !=couleur)
                    {
                        tab_coordonnees[j][0]=abscisse-1;
                        tab_coordonnees[j][1]=ordonnee-2;
                        *nb_case+=1;
                        j++;
                    }
                }
                break;
            case 3:
                if(abscisse-2>=0 && ordonnee-1>=0)
                {
                    if(Plateau[ordonnee-1][abscisse-2]==0 || (int)Plateau[ordonnee-1][abscisse-2]/100 !=couleur)
                    {
                        tab_coordonnees[j][0]=abscisse-2;
                        tab_coordonnees[j][1]=ordonnee-1;
                        *nb_case+=1;
                        j++;
                    }
                }
                break;
            case 4:
                if(abscisse-2>=0 && ordonnee+1<=7)
                {
                    if(Plateau[ordonnee+1][abscisse-2]==0 || (int)Plateau[ordonnee+1][abscisse-2]/100 !=couleur)
                    {
                        tab_coordonnees[j][0]=abscisse-2;
                        tab_coordonnees[j][1]=ordonnee+1;
                        *nb_case+=1;
                        j++;
                    }
                }
                break;
            case 5:
                if(abscisse-1>=0 && ordonnee+2<=7)
                {
                    if(Plateau[ordonnee+2][abscisse-1]==0 || (int)Plateau[ordonnee+2][abscisse-1]/100 !=couleur)
                    {
                        tab_coordonnees[j][0]=abscisse-1;
                        tab_coordonnees[j][1]=ordonnee+2;
                        *nb_case+=1;
                        j++;
                    }
                }
                break;
            case 6:
                if(abscisse+1<=7 && ordonnee+2<=7)
                {
                    if(Plateau[ordonnee+2][abscisse+1]==0 || (int)Plateau[ordonnee+2][abscisse+1]/100 !=couleur)
                    {
                        tab_coordonnees[j][0]=abscisse+1;
                        tab_coordonnees[j][1]=ordonnee+2;
                        *nb_case+=1;
                        j++;
                    }
                }
                break;
            case 7:
                if(abscisse+2<=7 && ordonnee+1<=7)
                {
                    if(Plateau[ordonnee+1][abscisse+2]==0 || (int)Plateau[ordonnee+1][abscisse+2]/100 !=couleur)
                    {
                        tab_coordonnees[j][0]=abscisse+2;
                        tab_coordonnees[j][1]=ordonnee+1;
                        *nb_case+=1;
                        j++;
                    }
                }
                break;
        }


     }
}

void remplissage_cases_fou(int tab_coordonnees[][2],int *nb_case,int abscisse,int ordonnee,int couleur,int Plateau[][8],int j){
    int i,arret_haut_droit=1,arret_haut_gauche=1,arret_bas_gauche=1,arret_bas_droit=1;
    for(i=1;i<8;i++)
    {
        if(arret_haut_droit)
        {
            if(abscisse+i<=7 && ordonnee-i>=0)
            {
                if(Plateau[ordonnee-i][abscisse+i]==0)
                {
                    tab_coordonnees[j][0]=abscisse+i;
                    tab_coordonnees[j][1]=ordonnee-i;
                    j++;
                    *nb_case +=1;
                }
                else if((int)Plateau[ordonnee-i][abscisse+i]/100==couleur)
                {
                    arret_haut_droit=0;
                }
                else if((int)Plateau[ordonnee-i][abscisse+i]/100!=couleur)
                {
                    tab_coordonnees[j][0]=abscisse+i;
                    tab_coordonnees[j][1]=ordonnee-i;
                    j++;
                    *nb_case +=1;
                    arret_haut_droit=0;
                }
            }
        }
        if(arret_haut_gauche)
        {
            if(abscisse-i>=0 && ordonnee-i>=0)
            {
                if(Plateau[ordonnee-i][abscisse-i]==0)
                {
                    tab_coordonnees[j][0]=abscisse-i;
                    tab_coordonnees[j][1]=ordonnee-i;
                    j++;
                    *nb_case +=1;
                }
                else if((int)Plateau[ordonnee-i][abscisse-i]/100==couleur)
                {
                    arret_haut_gauche=0;
                }
                else if((int)Plateau[ordonnee-i][abscisse-i]/100!=couleur)
                {
                    tab_coordonnees[j][0]=abscisse-i;
                    tab_coordonnees[j][1]=ordonnee-i;
                    j++;
                    *nb_case +=1;
                    arret_haut_gauche=0;
                }
            }
        }
        if(arret_bas_gauche)
        {
            if(abscisse-i>=0 && ordonnee+i<=7)
            {
                if(Plateau[ordonnee+i][abscisse-i]==0)
                {
                    tab_coordonnees[j][0]=abscisse-i;
                    tab_coordonnees[j][1]=ordonnee+i;
                    j++;
                    *nb_case +=1;
                }
                else if((int)Plateau[ordonnee+i][abscisse-i]/100==couleur)
                {
                    arret_bas_gauche=0;
                }
                else if((int)Plateau[ordonnee+i][abscisse-i]/100!=couleur)
                {
                    tab_coordonnees[j][0]=abscisse-i;
                    tab_coordonnees[j][1]=ordonnee+i;
                    j++;
                    *nb_case +=1;
                    arret_bas_gauche=0;
                }
            }
        }
        if(arret_bas_droit)
        {
            if(abscisse+i<=7 && ordonnee+i<=7)
            {
                if(Plateau[ordonnee+i][abscisse+i]==0)
                {
                    tab_coordonnees[j][0]=abscisse+i;
                    tab_coordonnees[j][1]=ordonnee+i;
                    j++;
                    *nb_case +=1;
                }
                else if((int)Plateau[ordonnee+i][abscisse+i]/100==couleur)
                {
                    arret_bas_droit=0;
                }
                else if((int)Plateau[ordonnee+i][abscisse+i]/100!=couleur)
                {
                    tab_coordonnees[j][0]=abscisse+i;
                    tab_coordonnees[j][1]=ordonnee+i;
                    j++;
                    *nb_case +=1;
                    arret_bas_droit=0;
                }
            }
        }
    }
}

void remplissage_cases_roi(int tab_coordonnees[][2],int *nb_case,int abscisse,int ordonnee,int couleur,int Plateau[][8]){
    int position[8][2]={{1,0},{1,-1},{0,-1},{-1,-1},{-1,0},{-1,1},{0,1},{1,1}};
    int i,j=0;
    for(i=0;i<8;i++)
    {
        if(ordonnee+position[i][1]>=0 && ordonnee+position[i][1]<=7 && abscisse+position[i][0]>=0 && abscisse+position[i][0]<=7)
        {
            if(Plateau[ordonnee+position[i][1]][abscisse+position[i][0]]==0 || (int)Plateau[ordonnee+position[i][1]][abscisse+position[i][0]]/100 !=couleur)
            {
                tab_coordonnees[j][0]=abscisse+position[i][0];
                tab_coordonnees[j][1]=ordonnee+position[i][1];
                j++;
                *nb_case +=1;
            }
        }
    }
}
