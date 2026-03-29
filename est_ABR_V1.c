/* est_ABR_V1.c */
#include <stdio.h>
#include <stdlib.h>
#include "est_ABR_V1.h"

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
int infixe_croissant(Arbre a, Noeud **dernier_noeud){
    if (a == NULL)
        return 1;
    if (!infixe_croissant(a->fg, dernier_noeud))
        return 0;
    if (*dernier_noeud != NULL && (*dernier_noeud)->valeur >= a->valeur)
        return 0;
    *dernier_noeud = a;
    return infixe_croissant(a->fd, dernier_noeud);
}

int est_abr_infixe(Arbre a){
    Noeud *dernier_noeud = NULL;
    return infixe_croissant(a, &dernier_noeud);
}