/* author : Nunemunthala Shiva
   Roll No. : 190001041
   email : cse190001041@iiti.ac.in
*/


#include <stdio.h>
#include <stdlib.h>

// our input takes pid attival time and burst time for each of the 
// process
struct input
{
    int pid, time_arrival, time_burst;
};

// our output outputs avg waiting time and turn around time
struct gantt_chart
{
    int pid, avg_time_wait, avg_time_turn_around;
};

// Compare function sorts based on arrival time
int compare(const void* a, const void* b);


// function to display list of processes and its burst time and 
//arrival time
void disp_procs(struct input proc[], int n);


// function to display gantt_chart 
void display_gantt_chart(struct gantt_chart g[], int n);


// our FCFS scheduling algorithm   takesinput,gantt_chart,num_processes
void FCFS(struct input procs[],struct gantt_chart *g, int num_processes);


int main(){
    int num_process;

    printf("Enter number of processes: ");
    scanf("%d",&num_process);

    struct input procs[num_process];

    // get process details from user
    for(int i=0;i<num_process;i++){
        procs[i].pid = i;
        printf("Process ID: %d\n", i);
        printf("Arrival Time: ");
        scanf("%d", &procs[i].time_arrival);
        printf("Burst Time: ");
        scanf("%d", &procs[i].time_burst);
    }

    printf("\n");

	// displaying our entered inouts
    disp_procs(procs,num_process);

    // sorting processes by arrival time
    qsort(procs,num_process,sizeof(struct input),compare);

    // creating output chart for given number of processes
    struct gantt_chart g[num_process];

    FCFS(procs,g,num_process);

    printf("\n");
    display_gantt_chart(g,num_process);
    printf("\n");

    float avg_time_wait = 0;
    float avg_time_turn_around = 0;


    for(int i=0;i<num_process;i++)
    {
        avg_time_wait += g[i].avg_time_wait;
        avg_time_turn_around += g[i].avg_time_turn_around;
    }

    avg_time_wait /= num_process;
   avg_time_turn_around /= num_process;

    printf("Average Waiting Time is : %f\n", avg_time_wait);
    printf("Average Turn Around Time is : %f\n", avg_time_turn_around);

    return 0;
}

int compare(const void* a, const void* b)
{
   struct input temp1 =  *((struct input*)a);
   struct input temp2 = *((struct input*)b);
   if(temp1.time_arrival < temp2.time_arrival)
   { 
   	return -1;
   }
   else if(temp1.time_arrival == temp2.time_arrival)
   { 
   	return 0;
   }	
   else
   {
   	return 1;
   }
}

void disp_procs(struct input proc[], int n)
{
    printf("displaying our inputs: \n");
    for(int i=0;i<n;i++)
    { 
    	printf("Process id: %d\t Burst time : %d\t arrival time : %d\n", proc[i].pid,proc[i].time_burst,proc[i].time_arrival);
    }
}

void display_gantt_chart(struct gantt_chart g[], int n)
{
    printf("Gantt Chart: \n");
    for(int i=0;i<n;i++)
     {
     	printf("process id : %d\t avg wait time : %d\t avg turn arount time : %d\n", g[i].pid,g[i].avg_time_wait,g[i].avg_time_turn_around);
     }
}

void FCFS(struct input procs[],struct gantt_chart *g, int num_processes)
{
    int t = 0;
    for(int i=0;i<num_processes;i++)
    {
        if(t<procs[i].time_arrival)
         t = procs[i].time_arrival;
        g[i].pid = procs[i].pid;
        g[i].avg_time_wait = t-procs[i].time_arrival;
        g[i].avg_time_turn_around = g[i].avg_time_wait+procs[i].time_burst;
        t += procs[i].time_burst;
    }
}

