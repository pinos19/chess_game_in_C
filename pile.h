#ifndef PILE_H_INCLUDED
#define PILE_H_INCLUDED


struct pile{
    char casep[3];
    struct pile *suivant;
};
typedef struct pile Pile;
Pile *empiler(Pile *haut_de_pile,char *casep);
void vider_pile(Pile *haut_de_pile);
#endif // PILE_H_INCLUDED
