////////////////////////////////////////////////////////////////
//
// This is a Pthread program to calculate the factorial of a
// given non-negative integer n.
//
// Compile:  gcc Factorial.c -o  Factorial -lpthread
//
// Run:      ./Factorial <n>
//
// Note:     n: a given non-negative integer
//
///////////////////////////////////////////////////////////////

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

int  factorial;  // Globle varialbe
void *Factorial(void *param);


int main(int argc, char *argv [])
{

  pthread_t tid;            // The thread identifier
  pthread_attr_t attr;      // The of thread attributes

  //The error checking is performed to ensure that the number of arguments is 2
  if (argc != 2)
  {
    fprintf(stderr, "usage: Factorial <integer value>\n");
    return -1;
  }

  //The error checking is performed to ensure that the given number is
  //a non-negative integer
  if (atoi(argv[1]) < 0)
  {
    fprintf(stderr, "<integer value> must be greater than zero.\n");
    return -1;
  }

  //Create a new thread and have it run the function Factorial
  pthread_create(&tid, NULL, Factorial, argv[1]);

  //Wait until the thread completes
  pthread_join(tid, NULL);

  printf("Factorial = %d\n", factorial);
}

 //The function to be run by the new created thread
void *Factorial(void *param)
 {
   int i, upper = atoi(param);
   factorial = 1;

   for (i = 1; i <= upper; i++)
	 factorial *= i;

   return NULL;
 }
