#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "genere_arbre_binaire.h"

void arbre_vers_dot(Arbre a, FILE *f){
    if (a == NULL) return;
    if (a->fg != NULL){
        fprintf(f, "  \"%p\" [label=\"%d\"];\n", (void*)a->fg, a->fg->valeur);
        fprintf(f, "  \"%p\" -> \"%p\";\n", (void*)a, (void*)a->fg);
        arbre_vers_dot(a->fg, f);
    }
    if (a->fd != NULL){
        fprintf(f, "  \"%p\" [label=\"%d\"];\n", (void*)a->fd, a->fd->valeur);
        fprintf(f, "  \"%p\" -> \"%p\";\n", (void*)a, (void*)a->fd);
        arbre_vers_dot(a->fd, f);
    }
}

void genere_dot(Arbre a, const char *nom_fichier){
    FILE *f = fopen(nom_fichier, "w");
    if (f == NULL) return;
    fprintf(f, "digraph {\n");
    if (a != NULL)
        fprintf(f, "  \"%p\" [label=\"%d\"];\n", (void*)a, a->valeur);
    arbre_vers_dot(a, f);
    fprintf(f, "}\n");
    fclose(f);
}

int main(){
    srand(time(NULL));
    Arbre a;
    ABR_quelconque_alea(&a, 50);
    if (a == NULL)
        printf("arbre NULL\n");
    else
        printf("racine : %d\n", a->valeur);
    genere_dot(a, "arbre.dot");
    return 0;
}