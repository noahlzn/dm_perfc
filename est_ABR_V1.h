/* est_ABR_V1.h */
 
#ifndef EST_ABR_V1_H
#define EST_ABR_V1_H
 
typedef struct noeud {
    int valeur;
    struct noeud *fg, *fd;
} Noeud, *Arbre;
 
/* Renvoie 1 si l'arbre binaire a est un ABR, 0 sinon. */
int est_abr_naif(Arbre a);
 
/* Renvoie 1 si l'arbre binaire a est un ABR, 0 sinon.
   Met à jour *min et *max avec le min et max de l'arbre si c'est un ABR. */
int est_abr_definition_aux(Arbre a, int *min, int *max);
 
/* Renvoie 1 si l'arbre binaire a est un ABR, 0 sinon. */
int est_abr_definition(Arbre a);
 
/* Parcours infixe (potentiellement incomplet) de l'arbre a.
   Renvoie 0 si l'ordre croissant est pas respecte, 1 sinon. */
int infixe_croissant(Arbre a, Noeud **dernier_noeud);
 
/* Renvoie 1 si l'arbre binaire a est un ABR via son parcours infixe, 0 sinon. */
int est_abr_infixe(Arbre a);
 
#endif