#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "Random.h"
#include "kernel.h"
#include "constants.h"

void print_banner(void);


unsigned int ilog2( unsigned int N)
{
    unsigned int exp=0;
    while ( (N = (N >> 1)) )
        exp++;

    return exp;
}


int main(int argc, char *argv[])
{
        /* default to the (small) cache-contained version */

     double min_time = RESOLUTION_DEFAULT;

     int FFT_size = FFT_SIZE;
     int SOR_size =  SOR_SIZE;
     int Sparse_size_M = SPARSE_SIZE_M;
     int Sparse_size_nz = SPARSE_SIZE_nz;
     int LU_size = LU_SIZE;

     int huge_flag = 0;



     /* run the benchmark */

     double res[6] = {0.0};
     double sum[6] = {0.0};   /* checksum */
     unsigned long num_cycles[6] = {0.0};
     Random R = new_Random_seed(RANDOM_SEED);


     if (argc > 1) 
     {
         int current_arg = 1;

         if (strcmp(argv[1], "-help")==0  ||
            strcmp(argv[1], "-h") == 0)
          {
              fprintf(stderr, "Usage: [-large | -huge #MB] [minimum_time]\n");
              exit(0);
          }

         if (strcmp(argv[1], "-large")==0)
         {
           FFT_size = LG_FFT_SIZE;
           SOR_size = LG_SOR_SIZE;
           Sparse_size_M = LG_SPARSE_SIZE_M;
           Sparse_size_nz = LG_SPARSE_SIZE_nz;
           LU_size = LG_LU_SIZE;
    
           current_arg++;
        }
        else if ((strcmp(argv[1], "-huge")==0) && (argc > 2))
        {
           
           unsigned int huge_cache_size = atoi(argv[2]) * ONE_MB;
           double dproblem_size = huge_cache_size / sizeof(double);
           double dsqrt_problem_size = sqrt(dproblem_size);

           unsigned int problem_size = floor(dproblem_size);
           unsigned int sqrt_problem_size = floor(dsqrt_problem_size);

           huge_flag = 1;
           
           if (argc<3)
           {
              fprintf(stderr, "Usage: [-large | -huge #MB] [minimum_time]\n");
              exit(0);
           }
           /* FFT_size = pow(2, floor(log2(dproblem_size)+1)); */
           FFT_size = 1 << ilog2(problem_size);
           SOR_size = sqrt_problem_size;
           Sparse_size_M = problem_size / 8;
           Sparse_size_nz = problem_size;
           LU_size = sqrt_problem_size;

           current_arg ++;
           current_arg ++;
        }




        if (current_arg < argc)
        {
          if (atof(argv[current_arg]) > 0.0)
             min_time = atof(argv[current_arg]);
        }
   
     }

  
 print_banner();
 printf("Using %10.2f seconds min time per kenel.", min_time);
 if (huge_flag)
 {
      printf(" Approx. problem size: %d (MB)", atoi(argv[2]));
 }
 printf("\n\n"); 
 
 /* print out results  */

 kernel_measureFFT( FFT_size, min_time, R, &res[1], &sum[1], &num_cycles[1]); 
 printf("FFT             Mflops: %8.2f    (N=%d) \n", res[1], 
            FFT_size);

 kernel_measureSOR( SOR_size, min_time, R, &res[2], &sum[2], &num_cycles[2]); 
 printf("SOR             Mflops: %8.2f    (%d x %d) \n", res[2], 
            SOR_size, SOR_size);

 kernel_measureMonteCarlo(min_time, R, &res[3], &sum[3], &num_cycles[3]); 
 printf("MonteCarlo:     Mflops: %8.2f  \n", res[3] );

 kernel_measureSparseMatMult( Sparse_size_M, 
          Sparse_size_nz, min_time, R, &res[4], &sum[4], &num_cycles[4]);    
  printf("Sparse matmult  Mflops: %8.2f    (N=%d, nz=%d)  \n", 
          res[4], Sparse_size_M, Sparse_size_nz);


 kernel_measureLU( LU_size, min_time, R, &res[5], &sum[5], &num_cycles[5]);  
 printf("LU              Mflops: %8.2f    (M=%d, N=%d) \n", res[5],
     LU_size, LU_size);



     res[0] = (res[1] + res[2] + res[3] + res[4] + res[5]) / 5;
     sum[0] = (sum[1] + sum[2] + sum[3] + sum[4] + sum[5]) / 5;


     printf("\n");
     printf("************************************\n");
     printf("Composite Score:       %8.2f\n" ,res[0]);
     printf("************************************\n");
     printf("\n");

     printf("FFT reps:              %ld\n", num_cycles[1]);
     printf("SOR reps:              %ld\n", num_cycles[2]);
     printf("Montel Carlo reps:     %ld\n", num_cycles[3]);
     printf("Sparse MatMult repss:  %ld\n", num_cycles[4]);
     printf("LU reps:               %ld\n", num_cycles[5]);
     printf("\n");
     printf("checksum:              %20.16e\n" ,sum[0]);

     Random_delete(R);

     return 0;
  
}

void print_banner()
{
 printf("**                                                              **\n");
 printf("** SciMark4 Numeric Benchmark, see http://math.nist.gov/scimark **\n");
 printf("** for details. (Results can be submitted to pozo@nist.gov)     **\n");
 printf("**                                                              **\n");
}
