//
//  mymatrix.c
//  
//
//  Created by umenohana on 07/10/2023.
//

#include <stdlib.h>
#include "mymatrix.h"

MyMatrix create_matrix(int nl, int nc)
{
    int i, j ;
    struct zmymatrix * tmp = malloc(sizeof(struct zmymatrix)) ;
    tmp->nl = nl ;
    tmp->nc = nc ;
    tmp->M = malloc(nl * sizeof(Data *)) ;
    for (i=0; i<nl; ++i)
    {
        tmp->M[i] = malloc(nc * sizeof(Data)) ;
        for (j=0; j<nc; ++j)
            tmp->M[i][j] = 0 ;
    }
    return tmp ;
}


void free_matrix(MyMatrix A)
{
    int i ;
    for (i=0; i<A->nl; ++i)
    {
        free(A->M[i]) ;
    }
    free(A->M) ;
    free(A) ;
}

void set_matrix(MyMatrix A, int i, int j, Data e)
{
    A->M[i][j] = e ;
}

Data get_matrix(MyMatrix A, int i, int j)
{
    return A->M[i][j] ;
}

void print_matrix(MyMatrix A)
{
    int i, j ;
    for (i=0; i<A->nl; ++i)
    {
        for (j=0; j<A->nc; ++j)
            printf("%d ", A->M[i][j]) ;
        printf("\n") ;
    }
}