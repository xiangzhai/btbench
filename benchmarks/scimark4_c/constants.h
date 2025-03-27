#ifndef CONSTANTS_H_
#define CONSTANTS_H_

     const  double RESOLUTION_DEFAULT = 2.0;  /* secs (normally 2.0) */
     const unsigned int RANDOM_SEED = 101010;

    /* default: small (cache-contained) problem sizes */

     const unsigned int FFT_SIZE = 1024;  /* (2^10) must be a power of two */
     const unsigned int SOR_SIZE =100; /* NxN grid */
     const unsigned int SPARSE_SIZE_M = 1000;
     const unsigned int SPARSE_SIZE_nz = 5000;
     const unsigned int LU_SIZE = 100;

    /* large (out-of-cache) problem sizes */

     const unsigned int LG_FFT_SIZE = 1048576;  /* (2^20) must be a power of two */
     const unsigned int LG_SOR_SIZE =1000;  /*  NxN grid  */
     const unsigned int LG_SPARSE_SIZE_M = 100000;
     const unsigned int LG_SPARSE_SIZE_nz =1000000;
     const unsigned int LG_LU_SIZE = 1000;


    /* huge (out-of-cache) problem sizes */
    /* (determined at runtime, but default to "large" sizes) */

     const unsigned int ONE_MB = 1048576;

     unsigned int HG_FFT_SIZE = 1048576;  /* (2^20) must be a power of two */
     unsigned int HG_SOR_SIZE =1000;  /*  NxN grid  */
     unsigned int HG_SPARSE_SIZE_M = 100000;
     unsigned int HG_SPARSE_SIZE_nz =1000000;
     unsigned int HG_LU_SIZE = 1000;



    /* tiny problem sizes (used to mainly to preload network classes     */
    /*                     for applet, so that network download times    */
    /*                     are factored out of benchmark.)               */
    /*                                                                   */
     const unsigned int TINY_FFT_SIZE = 16;  /* must be a power of two */
     const unsigned int TINY_SOR_SIZE =10; /* NxN grid */
     const unsigned int TINY_SPARSE_SIZE_M = 10;
     const unsigned int TINY_SPARSE_SIZE_N = 10;
     const unsigned int TINY_SPARSE_SIZE_nz = 50;
     const unsigned int TINY_LU_SIZE = 10;

#endif

