// To compile the following code use gcc -pthread -o threads_test threads_test.c
//./threads_test to execute


#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define SIZE 10 //Array size
//Global variables
int array[SIZE] = {8,23,-10,-24,13,32,6,18,42,76};//Array initiazed
int result[SIZE]; //Array to store the result
//Data structure defination
typedef struct
{
    int start;
    int end;
} parameters;

void *sorter(void *params) //Sort threads will call this function
{
    parameters* p = (parameters *)params;

    printf("The current thread id is %d\n",pthread_self());

    int begin = p->start;
    int end = p->end;

    printf("The begin index is %d\n",begin);
    printf("The end index is %d\n\n",end);

    int z;
    for(z = begin; z <= end; z++)
    {
    printf("The array obtained: %d \n", array[z]);
    }
    printf("\n");
    //Sorting the array
    int i,j,t,k;
    for(i=begin; i <= end; i++)
    {
      for(j=begin; j <= end-1; j++)
      {

        if(array[j] > array[j+1])
        {
            t = array[j];
            array[j] = array[j+1];
            array[j+1] = t;

        }
      }
    }
    //Displays the sorted array
    for(k = begin; k <= end; k++)
    {
      printf("The sorted array: %d\n", array[k]);
    }
    //Copies the sorted array to the result array
    int x;
    for(x=begin; x <= end; x++)
    {
      result[x]=array[x];
    }
    printf("\n");
    //Thread exits
    pthread_exit(NULL);
}

void *merger(void *params)//The merge thread will call this function
{
    parameters* p = (parameters *)params;
    int begin = p->start;
    int end = p->end;

    //Sorting of the result array
    int i,j,t;
    for(i=begin; i< end; i++)
    {
      for(j=begin; j< end-i; j++)
      {

        if(result[j] > result[j+1])
        {
            t = result[j];
            result[j] = result[j+1];
            result[j+1] = t;
        }
      }
    }

    int m;
    printf("The final sorted array is:\n");
    for(m=0; m <= SIZE-1; m++)
    {
        printf(" %d\n", result[m]);
    }
    pthread_exit(NULL);
}
void main ()
{
    int i;
    pthread_t sort_thread1;   //Initializing the threads
    pthread_t sort_thread2;
    pthread_t merge_thread;

    printf("\n");
    printf("\n");
    printf("-------------------Made by Megha Agarwal---------------------\n\n\n");
    //Assigning the values for thread 1
    parameters *data1 = (parameters *) malloc (sizeof(parameters));
    data1->start = 0;
    data1->end = (SIZE/2) - 1;
    pthread_create(&sort_thread1, 0, sorter, data1); //Creating the thread
    //Assigning the values for thread 2
    parameters *data2 = (parameters *) malloc (sizeof(parameters));
    data2->start = (SIZE/2);
    data2->end = SIZE - 1;
    pthread_create(&sort_thread2, 0, sorter, data2);
    //Waiting for threads  1 & 2 to finish execution
    pthread_join(sort_thread1, NULL);
    pthread_join(sort_thread2, NULL);
    //Assigning the values for thread 3
    parameters *data3 = (parameters *) malloc(sizeof(parameters));
    data3->start = 0;
    data3->end = SIZE-1;
    pthread_create(&merge_thread, 0, merger, data3);//Creating the merge thread after sort thread finish execution
    //Wait for the merge thread
    pthread_join(merge_thread, NULL);
    printf("\n");
    printf("\n");
    printf("***************************THANK YOU*******************************\n");


}
