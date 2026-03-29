/* est_ABR.c */
#include <stdio.h>
#include <stdlib.h>
#include "est_ABR.h"
#include "genere_arbre_binaire.h"

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
//definition
int est_abr_definition_aux(Arbre a, int *min, int *max, long long *nb_visites){
    if (a == NULL)
        return 1;

    (*nb_visites)++;

    int minG, maxG, minD, maxD;

    if (a->fg != NULL){
        if (!est_abr_definition_aux(a->fg, &minG, &maxG, nb_visites))
            return 0;
        if (maxG > a->valeur)
            return 0;
    }

    if (a->fd != NULL){
        if (!est_abr_definition_aux(a->fd, &minD, &maxD, nb_visites))
            return 0;
        if (minD < a->valeur)
            return 0;
    }

    *min = (a->fg != NULL) ? minG : a->valeur;
    *max = (a->fd != NULL) ? maxD : a->valeur;

    return 1;
}

int est_abr_definition(Arbre a, long long *nb_visites){
    int min, max;
    return est_abr_definition_aux(a, &min, &max, nb_visites);
}