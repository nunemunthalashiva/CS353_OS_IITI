/*
	author : Nunemunthala Shiva
	email	: cse190001041@iiti.ac.in
	Roll No : 190001041
*/

/* Note : Mam on my pc its always showing '0' probably because my host OS is stopping any race condition  so i tried it on cloud  so please consider the screenshot of the cloud one for this question
*/
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main()
{

    //returning a unique id given path and id
    key_t key = ftok("parent",72);

    //returning unique shared_signal memory id with permissions read and write 
    //to all users and groups
   
    int shm_id = shmget(key,2*sizeof(int),0666|IPC_CREAT);

    //attaching the shared_signal memory
    int* shared_signal = (int*) shmat(shm_id,NULL,0);
    
    // given in question that initially its 0
    *shared_signal = 0;

    int p1 = fork();

    if(p1 == 0)
    {
     //A's child proess   
     
     // we are acessing the shared part (we are not using any synchronization)
        int* shared_signal_A = (int*) shmat(shm_id,NULL,0);

        for(int i=0;i<100000;i++)
        {
            //here we are changing shared variable 
            (*shared_signal_A)++;
            // ending of critical section
        }

	// detaches address space
        shmdt(shared_signal_A);
    }
    //exactly similar to if statement code
    else
    {
        int p2 = fork();
        if(p2 == 0)
        {

            //B's Process 
	// we are acessing the shared part (we are not using any synchronization)
            int* shared_signal_B = (int*) shmat(shm_id,NULL,0);

            for(int i=0;i<100000;i++)
            {
                 //here we are changing shared variable 
                (*shared_signal_B)--;
                // ending of critical section
            }
            // detachesh shared address space
            shmdt(shared_signal_B);
        }
        else
        {
           // wait till child process complete their execution
            wait(NULL);
            wait(NULL);
            printf("Without implementing synchronization our X is: %d\n",*shared_signal);
            
            shmdt(shared_signal);
	 //IP_RMID marks the segment destroyed
            shmctl(shm_id,IPC_RMID,NULL);

        }
    }

    
}
