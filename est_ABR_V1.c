/* est_ABR_V1.c */
#include <stdio.h>
#include <stdlib.h>
#include "est_ABR_V1.h"

static Arbre alloue_noeud(int val){
    Arbre a = malloc(sizeof(Arbre));
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

int est_abr_naif(Arbre a){
    if (a == NULL)
        return 1;
    if (a->fg != NULL && abr_max(a->fg) > a->valeur)
        return 0;
    if (a->fd != NULL && abr_min(a->fd) < a->valeur)
        return 0;
    return est_abr_naif(a->fg) && est_abr_naif(a->fd);
}

int est_abr_definition_aux(Arbre a, int *min, int *max){
    if (!est_abr_naif(a))
        return 0;

    int vraimin = abr_min(a);
    int vraimax = abr_max(a);

    if (vraimin != *min)
        *min = vraimin;
    if (vraimax != *max)
        *max = vraimax;
    return 1;
}

int est_abr_definition(Arbre a){
    int min;
    int max;
    return est_abr_definition_aux(a,&min,&max);
}

int main(){
    Arbre a = alloue_noeud(5);
    a->fd = alloue_noeud(3);
    a->fg = alloue_noeud(4);
    printf("est abr : %d \n", est_abr_naif(a));
    printf("est abr full : %d \n", est_abr_naif(a));
    return 0;
}