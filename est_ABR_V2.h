/* est_ABR_V2.h */

#ifndef est_ABR_V2_H

#define est_ABR_V2_H

typedef struct noeud {
    int valeur;
    struct noeud *fg,*fd;
} Noeud, * Arbre;

/* renvoie 1 si l’arbre binaire a est bien un arbre binaire de recherche, 0
sinon. Celle-ci déterminera en plus le nombre de nœuds visités pour déterminer la valeur de retour */
int est_abr_naif(Arbre a, long long * nb_visites);

#endif

