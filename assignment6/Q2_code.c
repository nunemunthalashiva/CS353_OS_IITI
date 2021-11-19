#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include<sys/sem.h>

//wait on the semaphore to lock a resource
// locking a resource
int reserv(int semId, int semNum);


//signal on the semaphore Release a resource
int releas(int semId, int semNum);


int main()
{

   //returning a unique id given path and id
    key_t key = ftok("parent",72);

    //returning unique  memory id with permissions read and write 
    // to all users and groups
    int shm_id = shmget(key,2*sizeof(int),0666|IPC_CREAT);


    int sem_id_A, sem_id_B;
    int flag;

    // creating semaphore for A and returns semaphore identifier
    sem_id_A=semget(IPC_PRIVATE,1,0666|IPC_CREAT);
    //creating semaphore for B and returns semaphore identifier
    sem_id_B=semget(IPC_PRIVATE,1,0666|IPC_CREAT);
    semctl(sem_id_A,0,SETVAL,0);
    semctl(sem_id_B,0,SETVAL,1);

    //attaching shared memory
    int* shared_signal = (int*) shmat(shm_id,NULL,0);

// given in question that initially its 0
    *shared_signal = 0;

    int p1 = fork();

    if(p1 == 0)
    {

        //Child Process A

        int* shared_signal_A = (int*) shmat(shm_id,NULL,0);

        for(int i=0;i<100000;i++)
        {
         // wait on A until we lock shared variable of process b
            reserv(sem_id_A,0); 
            (*shared_signal_A)++;
            // release the variable for process b
            releas(sem_id_B,0);
        }


        shmdt(shared_signal_A);
    }
    else
    {

        int p2 = fork();
        if(p2 == 0)
        {

            //child Process B

            int* shared_signal_B = (int*) shmat(shm_id,NULL,0);

            for(int i=0;i<100000;i++)
            {
            // wait on B until we lock shared variable of process a
                reserv(sem_id_B,0); 
                (*shared_signal_B)--;
            // release the variable for process a
                releas(sem_id_A,0); 
            }
            shmdt(shared_signal_B);
        }
        else
        {
             // wait till child process complete their execution
            wait(NULL); 
            wait(NULL);
            printf("With implementing synchronization our shared variable is  %d\n",*shared_signal);
            
            shmdt(shared_signal);
	    //IP_RMID marks the segment destroyed
            shmctl(shm_id,IPC_RMID,NULL);

        }
    }

    
}

int reserv(int sem_id, int sem_num) 
{
// sem_buf has data fields short sem_num,sem_op,sem_flg
// to reserve semaphore
    struct sembuf reserve[1];
    
    // sem_num is like it specifies the specififc semaphore to be updated
    reserve[0].sem_num = sem_num;
    
    // semaphore operation for reserving 
    reserve[0].sem_op = -1;
    
    // operation flag ... 0 means no options are required
    reserve[0].sem_flg = 0;
    
    // semop returns 0 if successful else -1
    return semop(sem_id, reserve, 1);
}

int releas(int sem_id, int sem_num) 
{
    // sem_buf has data fields short sem_num,sem_op,sem_flg
    // this is for release the semaphore
    struct sembuf release[1];
    
    // sem_num is like it specifies the specififc semaphore to be updated
    release[0].sem_num = sem_num;
    
    // semaphore operation for releasing
    release[0].sem_op = 1;
    
    // operation flag ... 0 means no options are required
    release[0].sem_flg = 0;
    
    // semop returns 0 if successful else -1
    return semop(sem_id, release, 1);
}
