#include <stdio.h>
#include <stdlib.h>
#include "mymatrix.h"

struct MyMatrix_t {
    int nl, nc;
    int **data;
};

MyMatrix create_matrix(int nl, int nc) {
    struct MyMatrix_t *m = malloc(sizeof(struct MyMatrix_t));
    m->nl = nl;
    m->nc = nc;
    m->data = malloc(nl * sizeof(int*));
    for(int i=0; i<nl; i++) {
        m->data[i] = 0;
    }
    return m;
}

void free_matrix(MyMatrix A) {
    struct MyMatrix_t *m = A;
    for(int i=0; i < m->nl; i++) free(m->data[i]);
    free(m->data);
    free(m);
}

void set_matrix(MyMatrix A, int i, int j, Data e) {
    struct MyMatrix_t *m = A;
    if(i >= 0 && i < m->nl && j >= 0 && j < m->nc)
        m->data[i][j] = e;
}

Data get_matrix(MyMatrix A, int i, int j) {
    struct MyMatrix_t *m = A;
    if(i >= 0 && i < m->nl && j >= 0 && j < m->nc)
        return m->data[i][j];
    return 0;
}

void print_matrix(MyMatrix A) {
    struct MyMatrix_t *m = A;
    for(int i=0; i<m->nl; i++) {
        for(int j=0; j<m->nc; j++) {
            printf("%d ", get_matrix(A, i, j));
        }
        printf("\n");
    }
}