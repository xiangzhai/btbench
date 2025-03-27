#ifndef KERNEL_H
#define KERNEL_H

void kernel_measureFFT( unsigned int FFT_size, double min_time, Random R, 
      double *res, double *sum, unsigned long *num_cyles);

void kernel_measureSOR( unsigned int SOR_size, double min_time, Random R,
      double *res, double *sum, unsigned long *num_cyles);

void kernel_measureMonteCarlo( double min_time, Random R,
      double *res, double *sum, unsigned long *num_cyles);

void kernel_measureSparseMatMult(unsigned int Sparse_size_N,
    unsigned int Sparse_size_nz, double min_time, Random R,
      double *res, double *sum, unsigned long *num_cyles);

void kernel_measureLU( unsigned int LU_size, double min_time, Random R,
      double *res, double *sum, unsigned long *num_cyles);

#endif
