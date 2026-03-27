/* genere_arbre_binaire.h */

#ifndef GENERE_ARBRE_BINAIRE_H
#define GENERE_ARBRE_BINAIRE_H

#include "est_ABR.h"


/* construit un arbre binaire de taille n à partir de son codage*/
int construit_quelconque(Arbre * a, int ** codage, int n);

/* Renvoie le nombre de noeud dans le sous abre gauche à partir de son nombre 
de noeuds total */
int nb_noeuds_gauche(int n);

/* Renvoie un tableau du parcours prefixe d'un arbre à partir de son parcours infixe */
void parcours_infixe_2_prefixe_presque_complet(int *prefixe, int *infixe, int n)

#endif
