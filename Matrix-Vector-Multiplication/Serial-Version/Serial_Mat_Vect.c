/////////////////////////////////////////////////////////////////////////////////
//
// Purpose: This is a serial implementation of matrix-vector multiplication 
//          using one-dimensional arrays to store the vectors and the matrix.
//
// Compile: gcc Serial_Mat_Vect.c -o Serial_Mat_Vect 
// 
// Usage:   ./Serial_Mat_Vect
//
//////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

void Get_dims(int* m_p, int* n_p);
void Read_matrix(double A[], int m, int n);
void Read_vector(double x[], int n);
void Print_result(double y[], int m);
void Mat_vect_mult(double A[], double x[], double y[], int m, int n);


int main(void) 
{
   double* A = NULL;
   double* x = NULL;
   double* y = NULL;
   int m, n;

   Get_dims(&m, &n);

   A = malloc(m*n*sizeof(double));
   x = malloc(n*sizeof(double));
   y = malloc(m*sizeof(double));

   if (A == NULL || x == NULL || y == NULL) 
   {
      fprintf(stderr, "Can't allocate storage\n");
      exit(-1);
   }

   Read_matrix(A, m, n);
   Read_vector(x, n);

   Mat_vect_mult(A, x, y, m, n);

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
         scanf("%lf", &A[i*n+j]);
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


////////////////////////////////////////////////////////////////
//
// Purpose: Multiply a matrix by a vector
//
////////////////////////////////////////////////////////////////

void Mat_vect_mult(double A[], double x[], double y[], int m, int n) 
{
   int i, j;

   for (i = 0; i < m; i++) 
   {
      y[i] = 0.0;
      for (j = 0; j < n; j++)
         y[i] += A[i*n+j]*x[j];
   }
}  
