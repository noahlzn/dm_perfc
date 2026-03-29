/* main.c */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "est_ABR.h"
#include "genere_arbre_binaire.h"

#define NB_REPETITIONS 20

int main(void){
    srand(time(NULL));
    // 100 noeuds à 100000
    int tailles[] = {100, 500, 1000, 5000, 10000, 50000, 100000};
    int nb_tailles = 7;
    FILE *csv = fopen("mesures.csv", "w");
    fprintf(csv, "Taille;Morphologie;Methode;Nb_visites;Temps\n");
    // pour chaques tailles
    for (int t = 0; t < nb_tailles; t++){
        int n = tailles[t];
        printf("Taille %d\n", n);
        for (int r = 0; r < NB_REPETITIONS; r++){
            /* Generation des 6 arbres */
            Arbre pc_abr, pc_non, fi_abr, fi_non, qc_abr, qc_non;
            ABR_presque_complet_alea(&pc_abr, n);
            non_ABR_presque_complet_alea(&pc_non, n);
            ABR_filiforme_alea(&fi_abr, n);
            non_ABR_filiforme_alea(&fi_non, n);
            ABR_quelconque_alea(&qc_abr, n);
            non_ABR_quelconque_alea(&qc_non, n);
            Arbre arbres[] = {pc_abr, pc_non, fi_abr, fi_non, qc_abr, qc_non};
            const char *noms[] = {
                "presque_complet_ABR", "presque_complet_non_ABR",
                "filiforme_ABR",       "filiforme_non_ABR",
                "quelconque_ABR",      "quelconque_non_ABR"
            };
            // Mesures
            for (int m = 0; m < 6; m++){
                Arbre a = arbres[m];
                long long nb_visites;
                clock_t debut, fin;
                double temps;
                // Naif
                nb_visites = 0;
                debut = clock();
                est_abr_naif(a, &nb_visites);
                fin = clock();
                temps = (double)(fin - debut) / CLOCKS_PER_SEC;
                fprintf(csv, "%d;%s;naif;%lld;%.9f\n", n, noms[m], nb_visites, temps);
                // Definition
                nb_visites = 0;
                debut = clock();
                est_abr_definition(a, &nb_visites);
                fin = clock();
                temps = (double)(fin - debut) / CLOCKS_PER_SEC;
                fprintf(csv, "%d;%s;definition;%lld;%.9f\n", n, noms[m], nb_visites, temps);
                // Infixe
                nb_visites = 0;
                debut = clock();
                est_abr_infixe(a, &nb_visites);
                fin = clock();
                temps = (double)(fin - debut) / CLOCKS_PER_SEC;
                fprintf(csv, "%d;%s;infixe;%lld;%.9f\n", n, noms[m], nb_visites, temps);
            }
            // Liberation
            for (int m = 0; m < 6; m++)
                libere_arbre(arbres[m]);
        }
    }
    fclose(csv);
    return 0;
}