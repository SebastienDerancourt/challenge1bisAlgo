#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "mymatrix.h"

// Je déclare les tailles globales pour simplifier
// Pour l'exemple (j): 3x8, 8x4, 4x5, 5x2, 2x10, 10x20, 20x4, 4x3, 3x6, 6x12
// Ça fait 11 dimensions pour 10 matrices.
// dims[0]=3 (n1), dims[1]=8 (n2)... dims[10]=12 (n11)
int dims[] = {3, 8, 4, 5, 2, 10, 20, 4, 3, 6, 12};
// Pour le test (i) avec 3 matrices: 3x2, 2x4, 4x5
int dims_test[] = {3, 2, 4, 5};

// Fonction pour afficher le résultat de façon récursive
// On utilise la matrice B qui contient les endroits où on a coupé (les k)
void afficher_parenthesage(MyMatrix B, int i, int j) {
    if (i == j) {
        // Condition d'arrêt : une seule matrice
        printf("%d", i);
    } else {
        printf("(");
        // On récupère le k stocké
        int k = get_matrix(B, i, j);
        
        // Appel récursif gauche
        afficher_parenthesage(B, i, k);
        
        printf(",");
        
        // Appel récursif droit
        afficher_parenthesage(B, k + 1, j);
        printf(")");
    }
}

// Fonction principale qui fait tout le calcul
void calculer_optimisation(int n, int* dimensions) {
    // n est le nombre de matrices
    // On crée les matrices de taille n+1 x n+1 pour avoir les indices de 1 à n
    MyMatrix A = create_matrix(n + 1, n + 1); // Coûts
    MyMatrix B = create_matrix(n + 1, n + 1); // Découpes (k)

    int i, j, k, L, cout;
    
    // Initialisation : diagonale à 0
    for (i = 1; i <= n; i++) {
        set_matrix(A, i, i, 0);
    }

    // Boucle sur la longueur de la chaîne (de 2 matrices à n matrices)
    for (L = 2; L <= n; L++) {
        // Boucle sur le début de la chaîne i
        for (i = 1; i <= n - L + 1; i++) {
            j = i + L - 1; // Fin de la chaîne
            
            // On met une valeur très grande au début
            set_matrix(A, i, j, INT_MAX);
            
            // On teste toutes les coupures k possibles entre i et j-1
            for (k = i; k <= j - 1; k++) {
                
                // Formule du cours : p(i,k) + p(k+1,j) + ni*nk+1*nj+1
                // Attention aux indices du tableau dimensions :
                // La matrice Ai a pour lignes dimensions[i-1] et colonnes dimensions[i]
                // Donc ni -> dimensions[i-1]
                // nk+1 -> dimensions[k]
                // nj+1 -> dimensions[j]
                
                int cout_gauche = get_matrix(A, i, k);
                int cout_droite = get_matrix(A, k + 1, j);
                int cout_mult = dimensions[i - 1] * dimensions[k] * dimensions[j];
                
                cout = cout_gauche + cout_droite + cout_mult;

                // Si on trouve mieux, on garde
                if (cout < get_matrix(A, i, j)) {
                    set_matrix(A, i, j, cout);
                    set_matrix(B, i, j, k); // On sauvegarde le k optimal
                }
            }
        }
    }

    // Affichage des résultats
    printf("Coût minimal : %d\n", get_matrix(A, 1, n));
    printf("Parenthésage optimal : ");
    afficher_parenthesage(B, 1, n);
    printf("\n");

    // Nettoyage mémoire
    free_matrix(A);
    free_matrix(B);
}

int main() {
    printf("--- Test demandé (i) : 3 matrices ---\n");
    // 3 matrices, taille tableau dimensions 4
    calculer_optimisation(3, dims_test);

    printf("\n--- Challenge (j) : 10 matrices ---\n");
    // 10 matrices, taille tableau dimensions 11
    calculer_optimisation(10, dims);

    return 0;
}