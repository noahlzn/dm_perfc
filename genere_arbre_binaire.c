#include <stdio.h>
#include <stdlib.h>
#include "est_ABR.h"
#include "genere_arbre_binaire.h"


int construit_quelconque(Arbre *a, int **codage, int n) {
    // sous-arbre vide
    if (**codage == -1) {
        *a = NULL;
        (*codage)++;
        return 1;
    }
    *a = alloue_noeud(**codage);
    if (*a == NULL) return 0;
    (*codage)++;
    // Récursion gauche
    if (!construit_quelconque(&(*a)->fg, codage, n)) {
        libere_arbre(*a); // libère ce qui a été alloué
        *a = NULL;
        return 0;
    }
    // Récursion droite
    if (!construit_quelconque(&(*a)->fd, codage, n)) {
        libere_arbre(*a);
        *a = NULL;
        return 0;
    }
    return 1;
}

int main() {
    Arbre a = NULL;
    int codage[] = {1, 2, -1, -1, 3, -1, -1};
    int *ptr = codage;
    construit_quelconque(&a, &ptr, 3);
    return 0;
}
