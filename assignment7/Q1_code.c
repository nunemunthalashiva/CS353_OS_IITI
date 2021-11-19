/*
	Name : Nunemunthala Shiva
	email : cse190001041@iiti.ac.in
*/
//program for bankers algorithm

#include <stdio.h>
#include <stdlib.h>

int main()
{
    int num_res, num_procs;
    
    printf("Please enter number of processes : \n");
    scanf("%d", &num_procs);
    
    
    printf("Please enter number of resources :\n");
    scanf("%d", &num_res);
    
    // taking allocation matrix as input
    int allocation_matrix[num_procs][num_res];

    printf("Please enter allocation matrix\n");

    for (int i = 0; i < num_procs; i++)
    {
        for (int j = 0; j < num_res; j++)
        {
            scanf("%d", &allocation_matrix[i][j]);
        }
    }
    // taking max matrix as input
    int  MAX_matrix[num_procs][num_res];
    printf("Please enter maximum matrix\n");

    for (int i = 0; i < num_procs; i++)
    {
        for (int j = 0; j < num_res; j++)
        {
            scanf("%d", &MAX_matrix[i][j]);
        }
    }
    //taking availaible matrix as input
    int available_matrix[num_res];

    printf("Please enter available matrix\n");

    for (int i = 0; i < num_res; i++)
    {
        scanf("%d", &available_matrix[i]);
    }

    int request_resource[num_res], request_process;

    printf("Please enter requesting process\n");
    scanf("%d", &request_process);

    printf("Please enter array of request resources requested\n");
    
    //take request resource as input
    for(int i=0;i<num_res;i++)
    {
        scanf("%d",&request_resource[i]);
    }

    
    //check whether its safe or not for the current state 
    int is_safe = -1, work[num_res], finish[num_procs], sequence[num_procs];
    int k = 0;

    // calculating initially work matrix
    for (int i = 0; i < num_res; i++)
    {
        work[i] = available_matrix[i];
    }
    //calculating finish matrix
    for (int i = 0; i < num_procs; i++)
    {
        finish[i] = 0;
    }
    int j = 0;
    // code for checking safety
    while (is_safe == -1)
    {
        int i;
        for (i = 0; i < num_procs; i++)
        {
            int need = 1;
            for (int p = 0; p < num_res; p++)
            {
                if (MAX_matrix[i][p] - allocation_matrix[i][p] > work[p])
                {
                    need = 0;
                    break;
                }
            }
            if (need == 1 && finish[i] == 0)
            {
                for (int p = 0; p < num_res; p++)
                {
                    work[p] += allocation_matrix[i][p];
                }
                finish[i] = 1;
                sequence[j] = i;
                j++;
                break;
            }
        }

        if (i == num_procs)
        {
            if (j == num_procs)
            {
                is_safe = 1;
            }
            else
            {
                is_safe = 0;
            }
            break;
        }
    }

    if (is_safe == 0)
    {
        printf("Our given state is not safe\n");
    }
    else
    {
        printf("Our given state is safe\n");

        for (int i = 0; i < num_procs; i++)
        {
            printf("P%d ", sequence[i]);
        }
        printf("\n");
    }

    //end of checking for safety

    //check whether a particular request feasible or not

    for(int i=0;i<num_res;i++)
    {
        if(request_resource[i] > MAX_matrix[request_process][i] - allocation_matrix[request_process][i])
        {
            printf("Unable to give request as its beyond maximum\n");
            return 0;
        }
    }

    for(int i=0;i<num_res;i++)
    {
        if(request_resource[i] > available_matrix[i])
        {
            printf("No available requests to grant resources\n");
            return 0;
        }
    }

    for(int i=0;i<num_res;i++)
    {
        available_matrix[i]-=request_resource[i];
        allocation_matrix[request_process][i] += request_resource[i];
    }
    
    //check whether our granting request safe or not

    is_safe = -1;
    k = 0;

    for (int i = 0; i < num_res; i++)
    {
        work[i] = available_matrix[i];
    }

    for (int i = 0; i < num_procs; i++)
    {
        finish[i] = 0;
    }
    j = 0;
    while (is_safe == -1)
    {
        int i;
        for (i = 0; i < num_procs; i++)
        {
            int need = 1;
            // for a particular process checking whether work s greater than max-allocation then we change need to 0
            for (int p = 0; p < num_res; p++)
            {
                if (MAX_matrix[i][p] - allocation_matrix[i][p] > work[p])
                {
                    need = 0;
                    break;
                }
            }
            // if its safe and didnt finish
            if (need == 1 && finish[i] == 0)
            {
                for (int p = 0; p < num_res; p++)
                {
                    work[p] += allocation_matrix[i][p];
                }
                finish[i] = 1;
                sequence[j] = i;
                j++;
                break;
            }
        }

        if (i == num_procs)
        {
            if (j == num_procs)
            {
                is_safe = 1;
            }
            else
            {
                is_safe = 0;
            }
            break;
        }
    }

    if (is_safe == 0)
    {
        printf("Its unsafe to do operation so no request\n");
    }
    else
    {
	   printf("Printing updated allocation matrix\n");

        for(int i=0;i<num_procs;i++)
        {
            for(int j=0;j<num_res;j++)
            {
                printf("%d ",allocation_matrix[i][j]);
            }
            printf("\n");
        }
        printf("\nPrinting  updated need matrix\n");

        for(int i=0;i<num_procs;i++)
        {
            for(int j=0;j<num_res;j++)
            {
                printf("%d ",MAX_matrix[i][j]-allocation_matrix[i][j]);
            }
            printf("\n");
        }
        printf("\nPrinting updated available matrix\n");
        for(int i=0;i<num_res;i++)
        {
            printf("%d ",available_matrix[i]);
        }
        printf("\n");
    }
}
