#include <stdio.h>
#include <limits.h>
#include "mymatrix.h"

// initialisation de A
void init_A(int N[], int n, MyMatrix A)
{
    int i ;
    // initialisation de la diagonale de A à 0
    for (i = 1; i <= n; i++) {
        set_matrix(A, i, i, 0);
    }
}

// remplissage de A/B par ligne
void compute_A_B(int N[], int n, MyMatrix A, MyMatrix B)
{
    int i, j, k ;
    int min_val, min_pos, tmp ;
    
    for (i = n - 1; i >= 1; --i)
    {
        for (j = i + 1; j <= n; ++j)
        {
            // A [i][i] = 0
            // cout = A[i+1][j] + cout de multiplication
            min_val = get_matrix(A, i, i) + get_matrix(A, i + 1, j) + N[i] * N[i+1] * N[j+1];
            min_pos = i; // premiere coupure possible 

            // teste des coupures k entre i+1 et j-1
            for (k = i + 1; k < j; ++k)
            {
                tmp = get_matrix(A, i, k) + get_matrix(A, k + 1, j) + N[i] * N[k+1] * N[j+1]; // p(i, k) + p(k+1, j) + dim

                if (tmp < min_val)
                {
                    min_val = tmp;
                    min_pos = k;
                }
            }

            set_matrix(A, i, j, min_val);
            set_matrix(B, i, j, min_pos);
        }
    }
}

// calcul du parenthesage optimal 
void compute_opt_paren(MyMatrix B, int i, int j)
{
    int k ;
    if (i == j)
        printf("%d", i);
    else
    {
        printf("(");
        
        k = get_matrix(B, i, j);
        
        // partie gauche
        compute_opt_paren(B, i, k);
        
        printf(",");
        
        // partie droite
        compute_opt_paren(B, k + 1, j);
        printf(")");
    }
}


int main ()
{
    int ns[] = {3, 10}; // nombre de matrices
    int N3[]  = {0, 3, 2, 4, 5}; // tailles pour n = 3 (Question 3.i)
    int N10[] = {0, 3, 8, 4, 5, 2, 10, 20, 4, 3, 6, 12}; // tailles pour n = 10 (Question 3.j)

    int *testsN[] = {N3, N10};
    

    for (int t = 0; t < 2; ++t) { // boucle pour faire les test sur 3 puis 10 matrices
        int n = ns[t];
        int *N = testsN[t];

        printf("\e[4;32mTest sur %d matrices (Question 3.%c):\e[0m\n\n", n, 'i' + t);

        // sujet: Vous utiliserez des matrices de taille (n + 1) × (n + 1) dont vous n’utiliserez pas la première ligne/colonne (d’indice 0).
        MyMatrix A = create_matrix(n + 1, n + 1);
        MyMatrix B = create_matrix(n + 1, n + 1);

        init_A(N, n, A);
        compute_A_B(N, n, A, B);

        printf("Matrice A (Coûts): \n");
        print_matrix(A);
        printf("\n");
        printf("Matrice B (Découpes): \n");
        print_matrix(B);
        printf("\n");

        printf("Parenthésage optimal: ");
        compute_opt_paren(B, 1, n);
        printf("\n");
        printf("Nombre de produits nécessaires: %d\n\n", get_matrix(A, 1, n));

        free_matrix(A);
        free_matrix(B);
    }

    return 0 ;
}