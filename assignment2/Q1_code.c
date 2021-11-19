#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int compare (const void * t1, const void * t2) {
   return ( *(int*)t1 - *(int*)t2 );
}

void main(){
    int num_elems=10; // number of elements given in question: 10
    
    int shared_memory_id;//stores shared memory id
    
    int *arr;// declaring an array of 
    
    int size = sizeof(int)*num_elems;
    key_t key= 400 ;
    if ((shared_memory_id = shmget(key, size, IPC_CREAT | 0666)) < 0)
    {
        printf("Unfortunately got error while allocating memory\n");
        return;
    }

    if ((arr = shmat(shared_memory_id, NULL, 0)) == (int *) -1)
    {
        printf("Unfortunately got error while attachment \n");
        return;
    }

    printf("Please enter 10 elements ");
    for(int i=0;i<num_elems;i++){
        scanf("%d",&arr[i]);
    }

    
    // Declare 2 process ids
    int pid1,pid2;
    
    pid1=fork(); 
    
    // process with pid1 sorts the first 5 elements
    
    if(pid1==0)
    {
        qsort(arr,5,sizeof(int),compare);
        return;
    }
    else
    {
    //process with pid2 sorts next 5 elements
        pid2=fork();
        if(pid2==0)
        {
            qsort(arr+5,5,sizeof(int),compare);
            return;
        }
    }

    int status;

    //wait for our process to finish their work
    
    waitpid(pid1,&status,0);
    waitpid(pid2,&status,0);

    // declaring a temporary array to store the result
    int temp_array[num_elems];
    //trivial merge operation
    int i=0,r=num_elems/2,k=0;
    int lc=0,rc=0;
    while(i<num_elems/2 && r<num_elems)
    {
        if(arr[i]>arr[r])
        {
            temp_array[k++]=arr[r++];
        }
        else
        {
            temp_array[k++]=arr[i++];
        }
    }

    while(i<num_elems/2)
    {
        temp_array[k++]=arr[i++];
    }

    while(r<num_elems)
    {
        temp_array[k++]=arr[r++];
    }

    for(int i=0;i<num_elems;i++)
    {
        arr[i]=temp_array[i];
    }
    
    printf("Elements after sorting are ");
    for(int i=0;i<num_elems;i++)
    {
        printf("%d ",arr[i]);
    }
    
   
}
