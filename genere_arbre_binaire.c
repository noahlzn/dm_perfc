#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "genere_arbre_binaire.h"

Arbre alloue_noeud(int val){
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

int construit_quelconque(Arbre *a, int **codage, int n){
    // sous arbre vide
    if (**codage == -1) {
        *a = NULL;
        (*codage)++;
        return 1;
    }
    // allocation arbre
    *a = alloue_noeud(**codage);
    if (*a == NULL) 
        return 0;
    (*codage)++;
    // Fils gauche
    if (!construit_quelconque(&(*a)->fg, codage, n)){
        libere_arbre(*a);
        *a = NULL;
        return 0;
    }
    // Fils droite
    if (!construit_quelconque(&(*a)->fd, codage, n)){
        libere_arbre(*a);
        *a = NULL;
        return 0;
    }
    return 1;
}

int nb_noeuds_gauche(int n){
    if (n <= 1) {
        return 0;
    }

    int h = (int)floor(log2(n));
    int ni = pow(2, h) - 1; // nb noeud interne
    int nf = n - ni; // nb feuilles
    int max_feuilles_gauche = pow(2, h - 1);

    // si le nombre de feuilles est inferieur au max alors elles sont à gauche
    int feuilles_gauche;
    if (nf < max_feuilles_gauche){
        feuilles_gauche = nf;
    } else {
        // sinon ça déborde à droite
        feuilles_gauche = max_feuilles_gauche;
    }

    int ni_gauche = pow(2, h - 1) - 1;
    int noeuds_gauche = ni_gauche + feuilles_gauche;

    return noeuds_gauche;
}

void parcours_infixe_2_prefixe_presque_complet(int *prefixe, int *infixe, int n){
    if (n == 0)
        return;
    // racine
    int indice_racine = nb_noeuds_gauche(n);
    int racine = infixe[indice_racine];
    prefixe[0] = racine;
    // sous arbre gauche
    parcours_infixe_2_prefixe_presque_complet(prefixe + 1, infixe, indice_racine);
    // sous arbre droit
    parcours_infixe_2_prefixe_presque_complet(prefixe + 1 + indice_racine, infixe + indice_racine + 1, n - indice_racine - 1);
}

void parcours_infixe_2_prefixe_quelconque_aleatoire(int *codage, int *infixe, int n){
    if (n == 0){
        codage[0] = -1;
        return;
    }
    int k = rand() % n;
    codage[0] = infixe[k];
    // sous arbre gauche
    parcours_infixe_2_prefixe_quelconque_aleatoire(codage + 1, infixe, k);
    // sous arbre droit
    parcours_infixe_2_prefixe_quelconque_aleatoire(codage + 1 + (2*k+1), infixe + k+1, n-k-1);
}


int main(void){
    srand(time(NULL));
    int infixe[] = {8, 4, 9, 2, 10, 5, 1, 6, 3, 7};
    int prefixe[10];

    parcours_infixe_2_prefixe_quelconque_aleatoire(prefixe, infixe, 10);

    for (int i = 0; i < 10; i++){
        printf("%d ", prefixe[i]);
    }

    printf("\n");
    return 0;
}