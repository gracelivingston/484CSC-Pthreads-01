///////////////////////////////////////////////////////////////////////////////////////
//
// Purpose: This is a parallel implementation of matrix-vector multiplication. 
//          Matrix and vector are distributed by block rows and blocks, respectively.
//
// Compile: gcc Pth_Mat_Vect.c -o Pth_Mat_Vect -lpthread
// 
// Usage:   ./Pth_Mat_Vect <thread_count>
//
// Notes:
//         1.  Local storage for A, x, y is dynamically allocated.
//         2.  Number of threads(thread_count) should evenly divide both
//             m and n.The program doesn't check for this.
//         3.  We use a 1 - dimensional array for A and compute subscripts
//             using the formula A[i][j] = A[i*n + j]
//         4.  Distribution of A, x, and y is logical : all three are
//             globally shared.
//
///////////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Global variables
int     thread_count;
int     m, n;
double* A;
double* x;
double* y;

// Serial functions
void Get_dims(int* m_p, int* n_p);
void Read_matrix(double A[], int m, int n);
void Read_vector(double x[], int n);
void Print_result(double y[], int m);


// Parallel function 
void *Pth_mat_vect(void* rank);


int main(int argc, char* argv[]) 
{
   long       thread;
   pthread_t* thread_handles;

   if (argc != 2) 
     fprintf(stderr, "usage: pth_mat_vect <thread_count>\n");

   thread_count = atoi(argv[1]);
   thread_handles = malloc(thread_count*sizeof(pthread_t));

   Get_dims(&m, &n);

   A = malloc(m*n*sizeof(double));
   x = malloc(n*sizeof(double));
   y = malloc(m*sizeof(double));
   
   Read_matrix(A, m, n);

   Read_vector(x, n);

   for (thread = 0; thread < thread_count; thread++)
      pthread_create(&thread_handles[thread], NULL,
         Pth_mat_vect, (void*) thread);

   for (thread = 0; thread < thread_count; thread++)
      pthread_join(thread_handles[thread], NULL);

   Print_result(y, m);

   free(A);
   free(x);
   free(y);

   return 0;
}  


////////////////////////////////////////////////////////////////
//
// Purpose: Read the dimensions of the matrix from stdin
//
////////////////////////////////////////////////////////////////

void Get_dims(int* m_p, int* n_p)
{
	printf("Enter the number of rows\n");
	scanf("%d", m_p);
	printf("Enter the number of columns\n");
	scanf("%d", n_p);

	if (*m_p <= 0 || *n_p <= 0)
	{
		fprintf(stderr, "m and n must be positive\n");
		exit(-1);
	}
}  


////////////////////////////////////////////////////////////////
//
// Purpose: Read the contents of the matrix from stdin
//
////////////////////////////////////////////////////////////////

void Read_matrix(double A[], int m, int n)
{
	int i, j;

	printf("Enter the matrix A:\n");

	for (i = 0; i < m; i++)
		for (j = 0; j < n; j++)
			scanf("%lf", &A[i*n + j]);
}  


////////////////////////////////////////////////////////////////
//
// Purpose: Read a vector from stdin
//
////////////////////////////////////////////////////////////////

void Read_vector(double x[], int n)
{
	int i;

	printf("Enter the vector x:\n");

	for (i = 0; i < n; i++)
		scanf("%lf", &x[i]);
}  


////////////////////////////////////////////////////////////////
//
// Purpose: Multiply an mxn matrix by an nx1 column vector
//
////////////////////////////////////////////////////////////////

void *Pth_mat_vect(void* rank) 
{
   long my_rank = (long) rank;
   int i, j;

   int local_m = m/thread_count; 
  
   int my_first_row = my_rank*local_m;
   int my_last_row = (my_rank+1)*local_m - 1;

   for (i = my_first_row; i <= my_last_row; i++) 
   {
      y[i] = 0.0;
      for (j = 0; j < n; j++)
          y[i] += A[i*n+j]*x[j];
   }

   return NULL;
}  


////////////////////////////////////////////////////////////////
//
// Purpose: Print the contents of a vector to stdout
//
////////////////////////////////////////////////////////////////

void Print_result(double y[], int m)
{
	int i;

	printf("\nThe vector y:\n");
	for (i = 0; i < m; i++)
		printf("%f ", y[i]);
	printf("\n");
}  
