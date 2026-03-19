#include <stdio.h>
#include <stdlib.h>

typedef struct noeud {
    int valeur;
    struct noeud *fg, *fd;
} Noeud, * Arbre;

int abr_min(Arbre a){
    if (a == NULL)
        return 0;
    if (a->fg == NULL)
        return a->fg->valeur;
    return abr_min(a->fg);
}

int abr_max(Arbre a){
    if (a == NULL)
        return 0;
    if (a->fd == NULL)
        return a->fd->valeur;
    return abr_max(a->fd);
}