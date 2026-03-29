/* genere_arbre_binaire.h */

#ifndef GENERE_ARBRE_BINAIRE_H
#define GENERE_ARBRE_BINAIRE_H

#include "est_ABR.h"

/* Alloue un noeud avec val comme etiquette */
Arbre alloue_noeud(int val);

/* Libere l'espace memoire de l'arbre */
void libere_arbre(Arbre a);

/* Construit un arbre binaire a partir de son codage prefixe avec sentinelles -1 */
int construit_quelconque(Arbre *a, int **codage, int n);

/* Renvoie le nombre de noeuds dans le sous-arbre gauche d'un arbre presque complet a n noeuds */
int nb_noeuds_gauche(int n);

/* Transforme un parcours infixe en prefixe pour un arbre presque complet */
void parcours_infixe_2_prefixe_presque_complet(int *prefixe, int *infixe, int n);

/* Transforme un parcours infixe en prefixe pour un arbre filiforme choisi aleatoirement */
void parcours_infixe_2_prefixe_filiforme_aleatoire(int *prefixe, int *infixe, int n);

/* Transforme un parcours infixe en codage prefixe pour un arbre quelconque choisi aleatoirement */
void parcours_infixe_2_prefixe_quelconque_aleatoire(int *codage, int *infixe, int n);

/* Cree aleatoirement un ABR presque complet de taille noeuds */
int ABR_presque_complet_alea(Arbre *a, int taille);

/* Cree aleatoirement un arbre presque complet non-ABR de taille noeuds */
int non_ABR_presque_complet_alea(Arbre *a, int taille);

/* Cree aleatoirement un ABR de forme quelconque de taille noeuds */
int ABR_quelconque_alea(Arbre *a, int taille);

/* Cree aleatoirement un arbre quelconque non-ABR de taille noeuds */
int non_ABR_quelconque_alea(Arbre *a, int taille);

/* Cree aleatoirement un ABR filiforme de taille noeuds */
int ABR_filiforme_alea(Arbre *a, int taille);

/* Cree aleatoirement un arbre filiforme non-ABR de taille noeuds */
int non_ABR_filiforme_alea(Arbre *a, int taille);

#endif