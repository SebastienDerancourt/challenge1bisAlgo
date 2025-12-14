//
//  parenthesages.c
//  
//  Adapté pour l'exercice challenge
//

#include <stdio.h>
#include <limits.h> // Pour INT_MAX
#include "mymatrix.h"

void init_A(int N[], int n, MyMatrix A)
{
    int i ;
    // Initialisation de la diagonale de A à 0
    // (Le coût de multiplication d'une seule matrice est nul)
    for (i = 1; i <= n; i++) {
        set_matrix(A, i, i, 0);
    }
}

void compute_A_B(int N[], int n, MyMatrix A, MyMatrix B)
{
    int i, j, k, L ;
    int q ;
    
    // Remplissage de A et B
    // On procède par diagonales : d'abord les chaînes de longueur L=2, puis L=3, etc.
    for (L = 2; L <= n; L++) {
        for (i = 1; i <= n - L + 1; i++) {
            j = i + L - 1; // j est l'indice de fin de la chaîne
            
            // On initialise le coût à l'infini pour trouver le minimum
            set_matrix(A, i, j, INT_MAX);
            
            // On teste toutes les coupures k possibles entre i et j-1
            for (k = i; k <= j - 1; k++) {
                // Formule de récurrence : coût gauche + coût droit + coût combinaison
                // Dimensions : (N[i] x N[k+1]) * (N[k+1] x N[j+1])
                q = get_matrix(A, i, k) + get_matrix(A, k + 1, j) + N[i] * N[k+1] * N[j+1];
                
                // Si on trouve un coût plus petit, on met à jour
                if (q < get_matrix(A, i, j)) {
                    set_matrix(A, i, j, q);
                    set_matrix(B, i, j, k); // On sauvegarde l'indice de coupure k
                }
            }
        }
    }
}

void compute_opt_paren(MyMatrix B, int i, int j)
{
    int k ;
    // Conditions d'arrêt : si i == j, on affiche juste l'indice de la matrice
    if (i == j) {
        printf("%d", i);
    }
    else
    {
        printf("(");
        // On récupère le k optimal stocké dans B
        k = get_matrix(B, i, j);
        
        // Appel récursif pour la partie gauche
        compute_opt_paren(B, i, k);
        
        printf(",");
        
        // Appel récursif pour la partie droite
        compute_opt_paren(B, k + 1, j);
        printf(")");
    }
}


int main ()
{
    // Configuration pour le challenge (j) : 10 matrices
    const int n = 10;
    
    // Configuration pour le test (i) : 3 matrices (à décommenter pour tester)
    // const int n = 3;
    
    // Codage des tailles de matrices par un tableau N
    // Indices de 0 à n+1 pour correspondre à l'énoncé (N[i] x N[i+1])
    
    // Pour n=10
    int N[] = {0, 3, 8, 4, 5, 2, 10, 20, 4, 3, 6, 12};
    
    // Pour n=3 (à décommenter pour tester)
    // int N[] = {0, 3, 2, 4, 5};
    
    // Matrices A et B de taille (n+1)x(n+1)
    // On utilise les indices de 1 à n, donc il faut allouer n+1
    MyMatrix A = create_matrix(n + 1, n + 1);
    MyMatrix B = create_matrix(n + 1, n + 1);
    
    // Initialisation de A
    init_A(N, n, A);
    
    // Remplissage de A/B avec l'algo de programmation dynamique
    compute_A_B(N, n, A, B);
    
    // Affichage des matrices (optionnel pour les grandes tailles)
    printf("Matrice A (Coûts) :\n") ;
    print_matrix(A) ;
    // printf("Matrice B (Découpes) :\n") ;
    // print_matrix(B) ;
    
    // Résultat final
    printf("Parenthésage optimal :\n") ;
    compute_opt_paren(B, 1, n);
    printf("\n") ;
    printf("%d multiplications\n", get_matrix(A, 1, n)) ;
    
    // Nettoyage mémoire
    free_matrix(A);
    free_matrix(B);
    
    return 0 ;
}