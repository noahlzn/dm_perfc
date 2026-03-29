#include <stdio.h>
#include <stdlib.h>
#include "est_ABR_V2.h"

static Arbre alloue_noeud(int val){
    Arbre a = malloc(sizeof(Noeud));
    if (a != NULL){
        a->valeur = val;
        a->fg = NULL;
        a->fd = NULL;
    }
    return a;
}

void libere_arbre(Arbre a){
    if (a == NULL)
        return;
    libere_arbre(a->fg);
    libere_arbre(a->fd);
    free(a);
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
int est_abr_naif(Arbre a, long long *nb_visites){
    if (a == NULL)
        return 1;

    (*nb_visites)++;

    if (a->fg != NULL && abr_max(a->fg) > a->valeur)
        return 0;

    if (a->fd != NULL && abr_min(a->fd) < a->valeur)
        return 0;

    return est_abr_naif(a->fg, nb_visites) &&
           est_abr_naif(a->fd, nb_visites);
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

//infixe
int infixe_croissant(Arbre a, Noeud **dernier, long long *nb_visites){
    if (a == NULL)
        return 1;

    if (!infixe_croissant(a->fg, dernier, nb_visites))
        return 0;

    (*nb_visites)++;

    if (*dernier != NULL &&
        (*dernier)->valeur >= a->valeur)
        return 0;

    *dernier = a;

    return infixe_croissant(a->fd, dernier, nb_visites);
}

int est_abr_infixe(Arbre a, long long *nb_visites){
    Noeud *dernier = NULL;
    *nb_visites = 0;
    return infixe_croissant(a, &dernier, nb_visites);
}

int main(){
    long long nb_visites = 0;

    Arbre a = alloue_noeud(5);
    a->fg = alloue_noeud(4);
    a->fd = alloue_noeud(6);
    a->fd->fg = alloue_noeud(3);

    printf("naif : %d, visites : %lld\n",
           est_abr_naif(a, &nb_visites), nb_visites);

    nb_visites = 0;
    printf("definition : %d, visites : %lld\n",
           est_abr_definition(a, &nb_visites), nb_visites);

    nb_visites = 0;
    printf("infixe : %d, visites : %lld\n",
           est_abr_infixe(a, &nb_visites), nb_visites);

    libere_arbre(a);
    return 0;
}