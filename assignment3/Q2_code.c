#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>


// function declarations
int comparator_func(const void* ptr1,const void* ptr2);

void* sort(void* array);

void merge(int* array);


int main()
{
// given in program to take 10 elements as user input
    int array[10];
    printf("Please enter 10 elements space seperated\n");
    for(int i=0; i<10; i++)
    {
    	int c;
    	scanf("%d",&c);
    	array[i]=c;
    }

    pthread_t tid1, tid2;
    // create first thread which does sorting of
    // first 5 numbers
    pthread_create(&tid1, NULL, sort, (void*)(array));

    // crwate second thread which sorts our last 5 elements
    pthread_create(&tid2, NULL, sort, (void*)(array + 5));

    // wait for our threads to complete their respective works
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
    // merge array in the trivial way how merge sort works
    merge(array);

    for(int i=0;i<10;i++)
    {
        printf("%d ", array[i]);
        printf(" ");
    }
    printf("\n");
}

int comparator_func(const void* ptr1,const void* ptr2)
{
    int a = *((int*) ptr1);
    int b = *((int*) ptr2);
    return a - b;
}

// return a pointer to subarray which is sorted
// basically sorts first half and second half
void* sort(void* array)
{
    qsort(array, 5, sizeof(int), comparator_func);
}

// our naive implementation of merge in merge sort
void merge(int* array)
{
    int i = 0, j = 5, k = 0;
    int c[10];
    while(i < 5 && j < 10)
    {
        if(array[i] < array[j])
        {
        	c[k++] = array[i++];
        }
        else
        {
        	c[k++] = array[j++];
        }
    }
    while(i < 5)
    {
    	c[k++] = array[i++];
    }
    while(j < 10)
    {
    	 c[k++] = array[j++];
    }
    for(int i=0; i<10; i++)
    {
    	array[i] = c[i];
    }
}
