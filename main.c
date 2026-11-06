#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>

int rechElets_TabNonTries(int T[], int n, int x) {
    int i = 0;
    while (i < n && T[i] != x) {
        i++;
    }
    if (i < n) return 1; // Trouvé
    return 0;            // Non trouvé
}

int rechElets_TabTries(int T[], int n, int x) {
    int i = 0;
    while (i < n && T[i] < x) {
        i++;
    }
    if (i < n && T[i] == x) return 1; 
    return 0;                         
}
int rechElets_Dicho(int T[], int n, int x) {
int g = 0, d = n - 1;
    while (g <= d) {
        int m = g + (d - g) / 2;
        if (T[m] == x) return 1;
        if (T[m] < x) g = m + 1;
        else d = m - 1;
    }
    return 0;
}

double calculerTemps(int (*fonctionRecherche)(int[], int, int), int T[], int n, int x, int iterations) {
    clock_t start, end;
    
    start = clock();
    int k ;
    for ( k = 0; k < iterations; k++) {
        fonctionRecherche(T, n, x);
    }
    end = clock();
    
    return ((double)(end - start)) / CLOCKS_PER_SEC;
}


int main() {
    FILE *fichier = fopen("resultats_complexite.csv", "w");
    if (fichier == NULL) {
        printf("Erreur d'ouverture du fichier !\n");
        return 1;
    }
    fprintf(fichier, "n,NonTrie_Pire (s),Trie_Pire (s),Dicho_Pire (s)\n");
   
    int tailles[] = {100000, 200000, 400000, 600000, 800000, 1000000, 1200000, 1400000, 1600000, 1800000};
    int nb_tailles = 10;
    int iterations = 1000; // Nombre de répétitions pour lisser la mesure
     int x ;

     printf("Entrez la valeur de x a rechercher : ");
        scanf("%d", &x);
    printf("n\t\tNonTrie_Pire (s)\tTrie_Pire (s)\tDicho_Pire (s)\n");
      int t ;

    for ( t = 0; t < nb_tailles; t++) {
        int n = tailles[t];
        
        int *T = (int *)malloc(n * sizeof(int));
        if (T == NULL) {
            fclose(fichier);
            printf("Erreur d'allocation memoire pour n = %d\n", n);
            return 1;
        }

         int i ; 
        for ( i = 0; i < n; i++) {
            T[i] = i * 2; 
        }

        double temps_non_trie = calculerTemps(rechElets_TabNonTries, T, n, x, iterations);
        double temps_trie     = calculerTemps(rechElets_TabTries, T, n, x, iterations);
        double temps_dicho    = calculerTemps(rechElets_Dicho, T, n, x, iterations);

        printf("%d\t\t%f\t\t%f\t%f\n", n, temps_non_trie, temps_trie, temps_dicho);
        fprintf(fichier, "%d,%f,%f,%f\n", n, temps_non_trie, temps_trie, temps_dicho);
        free(T); 
    }
   fclose(fichier);
    printf("\nLes resultats ont ete enregistres dans 'resultats_complexite.csv'.\n");
    return 0;
}
