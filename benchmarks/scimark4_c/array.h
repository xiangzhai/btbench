
#ifndef ARRAY_H
#define ARRAY_H

double **new_Array2D_double(unsigned int M, unsigned int N);
void Array2D_double_delete(unsigned int M, unsigned int N, double **A);
void Array2D_double_copy(unsigned int M, unsigned int N, double **B, double **A);

#endif
