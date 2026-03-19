#include <stdio.h>
#include <stdlib.h>
#include "est_ABR.h"
#include "genere_arbre_binaire.h"


int construit_quelconque(Arbre *a, int **codage, int n) {
    if (n == 0) return 1;
    *a = alloue_noeud(**codage);
    if (*a == NULL) return 0;
    (*codage)++;  // consomme le nœud courant
    n--;
    if (n > 0 && **codage < (*a)->valeur)
        construit_quelconque(&(*a)->fg, codage, n);
    else
        construit_quelconque(&(*a)->fd, codage, n);
    return 1;
}

int main() {
    Arbre a = NULL;
    int codage[10] = {1, 2, 4, 8, 9, 5, 10, 3, 6, 7};
    int *ptr = codage;
    construit_quelconque(&a, &ptr, 10);
    printf("%d \n", a->valeur);
    return 0;
}