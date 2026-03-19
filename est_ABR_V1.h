/* est_ABR_V1.h */

#ifndef est_ABR_V1_H

typedef struct noeud {
    int valeur;
    struct noeud *fg,*fd;
} Noeud, * Arbre;

/* renvoie 1 si l’arbre binaire a est un arbre binaire de recherche, 0 sinon */
int est_abr_naif(Arbre a);

/* renvoie 1 si l’arbre binaire a est un arbre binaire de recherche, 0 sinon 
mets à jour les valeurs pointées par min et max uniquement lorsque l’arbre a est un arbre binaire de recherche */
int est_abr_definition_aux(Arbre a, int *min, int *max);

/* */
int est_abr_definition(Arbre a);
 
#define est_ABR_V1_H

#endif