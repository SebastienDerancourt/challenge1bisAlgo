//
//  mymatrix.h
//  
//
//  Created by umenohana on 07/10/2023.
//

#ifndef mymatrix_h
#define mymatrix_h

#include <stdio.h>

typedef int Data ;
struct zmymatrix {
    int nl, nc ;
    Data ** M ;
} ;
typedef struct zmymatrix * MyMatrix ;

MyMatrix create_matrix(int, int) ;
void free_matrix(MyMatrix) ;

void set_matrix(MyMatrix, int, int, Data) ;
Data get_matrix(MyMatrix, int, int) ;

void print_matrix(MyMatrix) ;

#endif /* mymatrix_h */