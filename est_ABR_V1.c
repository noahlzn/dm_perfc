#include <stdio.h>
#include <stdlib.h>
#include "est_ABR_V1.h"

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

//naif
int est_abr_naif(Arbre a){
    if (a == NULL)
        return 1;

    if (a->fg != NULL && abr_max(a->fg) > a->valeur)
        return 0;

    if (a->fd != NULL && abr_min(a->fd) < a->valeur)
        return 0;

    return est_abr_naif(a->fg) &&
           est_abr_naif(a->fd);
}

//definition optimisee
int est_abr_definition_aux(Arbre a, int *min, int *max){
    if (a == NULL)
        return 1;

    int minG, maxG, minD, maxD;

    if (a->fg != NULL){
        if (!est_abr_definition_aux(a->fg, &minG, &maxG))
            return 0;
        if (maxG > a->valeur)
            return 0;
    }

    if (a->fd != NULL){
        if (!est_abr_definition_aux(a->fd, &minD, &maxD))
            return 0;
        if (minD < a->valeur)
            return 0;
    }

    if (a->fg != NULL)
        *min = minG;
    else
        *min = a->valeur;

    if (a->fd != NULL)
        *max = maxD;
    else
        *max = a->valeur;

    return 1;
}

int est_abr_definition(Arbre a){
    int min, max;
    return est_abr_definition_aux(a, &min, &max);
}

//infixe
int infixe_croissant(Arbre a, Noeud **dernier){
    if (a == NULL)
        return 1;

    if (!infixe_croissant(a->fg, dernier))
        return 0;

    if (*dernier != NULL &&
        (*dernier)->valeur >= a->valeur)
        return 0;

    *dernier = a;

    return infixe_croissant(a->fd, dernier);
}

int est_abr_infixe(Arbre a){
    Noeud *dernier = NULL;
    return infixe_croissant(a, &dernier);
}

//test
int main(){
    Arbre a = alloue_noeud(5);
    a->fg = alloue_noeud(4);
    a->fd = alloue_noeud(6);
    a->fd->fg = alloue_noeud(3); //pas abr

    printf("naif : %d\n", est_abr_naif(a));
    printf("definition : %d\n", est_abr_definition(a));
    printf("infixe : %d\n", est_abr_infixe(a));

    return 0;
}