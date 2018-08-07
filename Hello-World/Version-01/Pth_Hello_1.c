//////////////////////////////////////////////////////////////////////////
//
// Purpose:  Create a single thread and print a message.
//
// Compile:  gcc Pth_Hello_1.c -o Pth_Hello_1 -lpthread
// 
// Usage:    ./Pth_Hello_1
//
///////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>


void * Hello_Fun()
{

  printf("Hello World!\n");

  return NULL;
}


int main(int argc, char * argv[])
{

  pthread_t thread;  //Thread identifier

  //Create a new thread to have it run the function Hello_Fun
  pthread_create(&thread, NULL, Hello_Fun, NULL);

  //Wait until the thread completes
  pthread_join(thread, NULL);

  return 0;
}

