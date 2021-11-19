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
    int pid;
    int time_arrival;
    int time_burst;
};

// gantt chart structure contains pointer to next proc 
struct gantt_chart
{
    int time_arrival, time_burst, pid;
    struct gantt_chart *next;
};

int compare(const void* a, const void* b);


void round_robin(struct input arr[], int n, int time_quanta, int context_switch_time);



int main()
{
// num_procs is the number of processors we want to calculate
    int num_procs;
    printf("Enter number of process : ");
    scanf("%d", &num_procs);
    struct input arr[num_procs];
    // taking input of procs ids , its arrival time , waiting time
    for(int i=1; i<=num_procs; i++)
    {
        printf("\nPlease enter PID of %dth process ", i);
        scanf("%d", &arr[i-1].pid);
        printf("\nPlease enter arrival time of process ");
        scanf("%d", &arr[i-1].time_arrival);
        printf("\nPlease enter burst time: ");
        scanf("%d", &arr[i-1].time_burst);
    }
    // time quanta for round robin scheduling
    int time_quanta;
    printf("\nPlease enter time quanta for round robin :");
    scanf("%d", &time_quanta);
    int context_switch_time;
    printf("\nPlease enter context switching time ");
    scanf("%d", &context_switch_time);
    qsort(arr, num_procs, sizeof(struct  input), compare);
    round_robin(arr, num_procs, time_quanta, context_switch_time);
    return 0;
}

// compare function for quick sort algorithm
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

void round_robin(struct input arr[], int n, int time_quanta, int context_switch_time)
{
    struct input queue[n];
    
    // storing turn around time of n procs
    int turn_around_time[n];
    // fromt rear points to time_arrivaling and last position of queue
    //initially queue is empty so both are -1
    int front = -1;
    int rear = -1;
    // this variable keeps track of number of context switches
    int num_context_switches = 0;
    
    struct gantt_chart *cureent_ptr = (struct gantt_chart*) malloc(sizeof(struct gantt_chart));
    cureent_ptr->next = NULL;
    struct gantt_chart *temp_ptr = cureent_ptr;
    double total_burst_time = 0.0;
    // summing up burst times of all processes
    for(int i=0; i<n; i++)
    {
    	 total_burst_time += 1.0 * arr[i].time_burst;
    }
    int current_ptr_burst_time = 0, index = 0, turn_around_time_index = 0;
    do
    {
    // check if queue is empty and current burst timr is less than 
    // arrival time of 'index' th process
        if(front == -1 && rear == -1 && index < n && arr[index].time_arrival >= current_ptr_burst_time)
        {
            if(arr[index].time_arrival > current_ptr_burst_time)
            {
                cureent_ptr->time_arrival = current_ptr_burst_time;
                cureent_ptr->time_burst = arr[index].time_arrival;
                cureent_ptr->pid = -2;
                cureent_ptr->next = (struct gantt_chart*) malloc(sizeof(struct gantt_chart));
                cureent_ptr = cureent_ptr->next;
                cureent_ptr->next = NULL;
            }
            current_ptr_burst_time = arr[index].time_arrival;
            front = 0;
            rear = 0;
            queue[rear] = arr[index];
            index++;
        }
        // present points the front part of queue
        struct input present = queue[front];
        // if both points to same value that means our queue is empty
        if(front == rear)
        {
            front = -1;
            rear = -1;
        }
        // or else we increment queue Note here we are implementing circular queue
        else 
        {
        	front = (front + 1) % n;
        }
        cureent_ptr->time_arrival = current_ptr_burst_time;
        cureent_ptr->pid = present.pid;
        //if our time burst is greater than time quanta
        // we exectue that process for one quanta and append that process to 
        // last of queue.
        
        // This is standard queue implementation
        if(present.time_burst > time_quanta)
        {
            cureent_ptr->time_burst = cureent_ptr->time_arrival + time_quanta;
            present.time_burst -= time_quanta;
            current_ptr_burst_time = cureent_ptr->time_burst;
            while(index < n && arr[index].time_arrival <= (current_ptr_burst_time))
            {
                if(front == -1 && rear == -1)
                {
                    front = 0;
                    rear = 0;
                }
                else rear = (rear + 1) % n;
                queue[rear] = arr[index];
                index++;
            }
            if(front == -1 && rear == -1)
            {
                front = 0;
                rear = 0;
            }
            else rear = (rear + 1) % n;
            queue[rear] = present;
        }
        // if time quanta is greater than cpu burst time
        
        else
        {
            cureent_ptr->time_burst = cureent_ptr->time_arrival + present.time_burst;
            turn_around_time[turn_around_time_index] =  cureent_ptr->time_burst - present.time_arrival;
            turn_around_time_index++;
            current_ptr_burst_time = cureent_ptr->time_burst;
            while(index < n && arr[index].time_arrival <= current_ptr_burst_time)
            {
                if(front == -1 && rear == -1)
                {
                    front = 0;
                    rear = 0;
                }
                else rear = (rear + 1) % n;
                queue[rear] = arr[index];
                index++;
            }
        }
        if(front != -1 && rear != -1)
        {
            cureent_ptr->next = (struct gantt_chart*) malloc(sizeof(struct gantt_chart));
            cureent_ptr = cureent_ptr->next;
            cureent_ptr->next = NULL;
            cureent_ptr->time_arrival = current_ptr_burst_time;
            cureent_ptr->time_burst = current_ptr_burst_time + context_switch_time;
            cureent_ptr->pid = -1;
            num_context_switches++;
        }
        cureent_ptr->next = (struct gantt_chart*) malloc(sizeof(struct gantt_chart));
        cureent_ptr = cureent_ptr->next;
        cureent_ptr->next = NULL;
        current_ptr_burst_time += context_switch_time;
    }
    while((front != -1 && rear != -1) || index < n);
    printf("\n Gantt Chart: ");
    int count = 1;
    while(temp_ptr->next)
    {
        printf("\n");
        if(temp_ptr->pid >= 0)
        {
            printf("\n %d. process%d, %d, %d", count, temp_ptr->pid, temp_ptr->time_arrival, temp_ptr->time_burst);
        }
        else if(temp_ptr->pid == -2)
        {
            printf("\n %d. idle right now, %d, %d", count, temp_ptr->time_arrival, temp_ptr->time_burst);
         }
        else
            printf("\n %d. context switch, %d, %d", count, temp_ptr->time_arrival, temp_ptr->time_burst);
        temp_ptr = temp_ptr->next;
        count++;
    }
    printf("\nNumber of context switches occured in this schecduling is : %d", num_context_switches);
    double CPU_util = (total_burst_time) / (total_burst_time + num_context_switches * context_switch_time);
    printf("\nCPU Utilization is : %f", CPU_util);
    double total = 0.0;
    for(int i=0; i<n; i++)
    {
    	 total += 1.0 * turn_around_time[i];
    }
    printf("\nAverage Turnaround Time: %f", total / n);
}

