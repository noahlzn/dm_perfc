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

int infixe_croissant(Arbre a, Noeud **dernier_noeud, long long *nb_visites) {
    if (a == NULL)
        return 1;
    if (!infixe_croissant(a->fg, dernier_noeud, nb_visites))
        return 0;
    (*nb_visites)++;
    if (*dernier_noeud != NULL && (*dernier_noeud)->valeur >= a->valeur)
        return 0;
    *dernier_noeud = a;
    return infixe_croissant(a->fd, dernier_noeud, nb_visites);
}

int est_abr_infixe(Arbre a, long long *nb_visites) {
    Noeud *dernier_noeud = NULL;
    *nb_visites = 0;
    return infixe_croissant(a, &dernier_noeud, nb_visites);
}

int est_abr_definition_aux(Arbre a, int *min, int *max, long long *nb_visites){
    if (a == NULL)
        return 1;

    (*nb_visites)++;

    int minG, maxG, minD, maxD;

    //sous arbre gauche
    if (a->fg != NULL){
        if (!est_abr_definition_aux(a->fg, &minG, &maxG, nb_visites))
            return 0;
        if (maxG > a->valeur)
            return 0;
    }

    //sous arbre droit
    if (a->fd != NULL){
        if (!est_abr_definition_aux(a->fd, &minD, &maxD, nb_visites))
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

int main(){
    long long nb_visites = 0;
    Arbre a = alloue_noeud(5);
    a->fd = alloue_noeud(6);
    a->fd->fg = alloue_noeud(3);
    a->fg = alloue_noeud(4);
    printf("est abr : %d \nnb visites : %lld \n", est_abr_naif(a, &nb_visites), nb_visites);
    return 0;
}

