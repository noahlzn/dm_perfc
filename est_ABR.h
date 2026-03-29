/* est_ABR.h */
 
#ifndef EST_ABR_H
#define EST_ABR_H
 
typedef struct noeud {
    int valeur;
    struct noeud *fg, *fd;
} Noeud, *Arbre;
 
/* Renvoie 1 si l'arbre binaire a est un ABR, 0 sinon.
   Incrémente *nb_visites du nombre de noeuds visités. */
int est_abr_naif(Arbre a, long long *nb_visites);
 
/* Renvoie 1 si l'arbre binaire a est un ABR, 0 sinon.
   Met à jour *min et *max avec le min et max de l'arbre si c'est un ABR.
   Incrémente *nb_visites du nombre de noeuds visités. */
int est_abr_definition_aux(Arbre a, int *min, int *max, long long *nb_visites);
 
/* Renvoie 1 si l'arbre binaire a est un ABR, 0 sinon.
   Incrémente *nb_visites du nombre de noeuds visités. */
int est_abr_definition(Arbre a, long long *nb_visites);
 
/* Parcours infixe de l'arbre a.
   Renvoie 0 si l'ordre croissant n'est pas respecte, 1 sinon.
   Incrémente *nb_visites du nombre de noeuds visités. */
int infixe_croissant(Arbre a, Noeud **dernier_noeud, long long *nb_visites);
 
/* Renvoie 1 si l'arbre binaire a est un ABR, 0 sinon.
   Incrémente *nb_visites du nombre de noeuds visités. */
int est_abr_infixe(Arbre a, long long *nb_visites);

#endif

