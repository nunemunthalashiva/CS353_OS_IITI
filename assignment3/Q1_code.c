#include<stdio.h>
#include<unistd.h>
#include<pthread.h>

int array[100]; // our array is being shared by our threads

//  function declarations
void* fibonacci(void* n);


int main(){
    int num_size;
    // user enters number of fibinocci he wants
    printf("Please enter number of fibinocci numbers you want\n");
    scanf("%d", &num_size);
    // identifier our of our new thread we are going to create
    pthread_t tid;
    // creates our new thread

    pthread_create(&tid,NULL,fibonacci, (void*) &num_size);
    // wait for all the child threads to complete and then our
    // parent thread prints the numbers
    pthread_join(tid, NULL);

    for(int i=0; i<num_size; i++)
    {
    	printf("%d ", array[i]);
    	printf(" ");
    }
     printf("\n");
    return 0;
}

// naive implementation of fibinoccai
void* fibonacci(void* n)
{
    int num = *((int*) n);
    array[0] = 0;
    array[1] = 1;
    for(int i=2; i<num; i++)
    {
        array[i] = array[i-1] + array[i-2];
    }
};
