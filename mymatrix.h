#ifndef MYMATRIX_H
#define MYMATRIX_H
typedef int Data;
typedef void* MyMatrix;
MyMatrix create_matrix(int nl, int nc);
void free_matrix(MyMatrix A);
void set_matrix(MyMatrix A, int i, int j, Data e);
Data get_matrix(MyMatrix, int, int);
void print_matrix(MyMatrix);
#endif