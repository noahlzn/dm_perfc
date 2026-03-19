/* est_ABR.c */

#include <stdio.h>
#include <stdlib.h>
#include "est_ABR.h"

static Arbre alloue_noeud(int val){
    Arbre a = malloc(sizeof(Noeud));
    if (a != NULL){
        a->valeur = val;
        a->fg = NULL;
        a->fd = NULL;
    }
    return a;
}

static int abr_min(Arbre a){
    while (a->fg != NULL)
        a = a->fg;
    return a->valeur;
}

static int abr_max(Arbre a){
    while (a->fd != NULL)
        a = a->fd;
    return a->valeur;
}

int est_abr_naif(Arbre a, long long *nb_visites){
    if (a == NULL)
        return 1;
    (*nb_visites)++;
    if (a->fg != NULL && abr_max(a->fg) > a->valeur)
        return 0;
    if (a->fd != NULL && abr_min(a->fd) < a->valeur)
        return 0;
    return est_abr_naif(a->fg, nb_visites) && est_abr_naif(a->fd, nb_visites);
}

int main(){
    long long nb_visites = 0;
    Arbre a = alloue_noeud(5);
    a->fd = alloue_noeud(6);
    a->fd->fg = alloue_noeud(3);
    a->fg = alloue_noeud(4);
    printf("est abr : %d \nnb visites : %lld \n", est_abr_naif(a, &nb_visites), nb_visites);
    return 0;
}