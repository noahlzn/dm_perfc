#include <stdio.h>
#include <stdlib.h>
#include <maths.h>
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

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "est_ABR.h"
#include "genere_arbre_binaire.h"

int construit_quelconque(Arbre *a, int **codage, int n) {
    // sous arbre vide
    if (**codage == -1) {
        *a = NULL;
        (*codage)++;
        return 1;
    }

    *a = alloue_noeud(**codage);
    if (*a == NULL) return 0;

    (*codage)++;

    // Recursion gauche
    if (!construit_quelconque(&(*a)->fg, codage, n)) {
        libere_arbre(*a);
        *a = NULL;
        return 0;
    }

    // Recursion droite
    if (!construit_quelconque(&(*a)->fd, codage, n)) {
        libere_arbre(*a);
        *a = NULL;
        return 0;
    }

    return 1;
}

int nb_noeuds_gauche(int n) {
    if (n <= 1) {
        return 0;
    }

    int h = (int)floor(log2(n));
    int ni = pow(2, h) - 1;
    int feuilles = n - ni;
    int max_feuilles_gauche = pow(2, h - 1);

    // si le nombre de feuilles est inferieur au max alors elles sont à gauche
    int feuilles_gauche;
    if (feuilles < max_feuilles_gauche) {
        feuilles_gauche = feuilles;
    } else {
        // sinon ça déborde à droite
        feuilles_gauche = max_feuilles_gauche;
    }

    int ni_gauche = pow(2, h - 1) - 1;
    int noeuds_gauche = ni_gauche + feuilles_gauche;

    return noeuds_gauche;
}

void parcours_infixe_2_prefixe_presque_complet(int *prefixe, int *infixe, int n) {
    if (n == 0)
        return;

    int indice_racine = nb_noeuds_gauche(n);
    int racine = infixe[indice_racine];

    prefixe[0] = racine;

    // sous arbre gauche
    parcours_infixe_2_prefixe_presque_complet(prefixe + 1, infixe, indice_racine);

    // sous arbre droit
    parcours_infixe_2_prefixe_presque_complet(
        prefixe + 1 + indice_racine,
        infixe + indice_racine + 1,
        n - indice_racine - 1
    );
}

int main(void) {
    for (int i = 0; i < 13; i++) {
        printf("%d %d\n", i, nb_noeuds_gauche(i));
    }

    int infixe[] = {8, 4, 9, 2, 10, 5, 1, 6, 3, 7};
    int prefixe[10];

    parcours_infixe_2_prefixe_presque_complet(prefixe, infixe, 10);

    for (int i = 0; i < 10; i++) {
        printf("%d ", prefixe[i]);
    }

    printf("\n");
    return 0;
}
