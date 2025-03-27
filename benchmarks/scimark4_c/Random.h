typedef struct
{
  int m[17];                        
  int seed;                             
  int i;                                /* originally = 4 */
  int j;                                /* originally =  16 */
  int /*boolean*/ haveRange;            /* = false; */
  double left;                          /*= 0.0; */
  double right;                         /* = 1.0; */
  double width;                         /* = 1.0; */
}
Random_struct, *Random;

Random new_Random_seed(int seed);
double Random_nextDouble(Random R);
void Random_delete(Random R);
double *RandomVector(unsigned int N, Random R);
double **RandomMatrix(unsigned int M, unsigned int N, Random R);
