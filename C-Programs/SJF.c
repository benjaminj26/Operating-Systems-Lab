#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Process
{
	int process_id;
	int burst_time;
	int waiting_time;
	int turn_around_time;
};

void insertion_sort(struct Process *processes, int size)
{
    for(int i=1; i<size; ++i)
    {
        struct Process key = processes[i];
        int j;
        for(j=i-1; j>=0 && key.burst_time < processes[j].burst_time; --j)
        {
            processes[j+1] = processes[j];
        }
        processes[j+1] = key; 
    }
}

void display_results(struct Process *processes, int size)
{
	printf("\nProcess Number\t Burst Time\t Waiting Time\t Turn Around Time\n");
	for(int i=0; i<size; ++i)
	{
		printf("%d\t\t %d\t\t %d\t\t %d\n", processes[i].process_id, processes[i].burst_time, processes[i].waiting_time, processes[i].turn_around_time);
	}
	float avg_waiting_time = 0;
	float avg_turn_around_time = 0;
	for(int i=0; i<size; ++i)
	{
		avg_waiting_time += processes[i].waiting_time;
		avg_turn_around_time += processes[i].turn_around_time;
	}
	
	avg_waiting_time /= size;
	avg_turn_around_time /= size;
	
	printf("Average Waiting Time = %f\n", avg_waiting_time);
	printf("Average Turn Around Time = %f\n", avg_turn_around_time);
}

void sjf(struct Process *processes, int size)
{
	struct Process *sorted = (struct Process *)calloc(size, sizeof(struct Process));
	
	for(int i=0; i<size; ++i)
	{
		sorted[i] = processes[i];
	}
	// memmove(sorted, processes, size*sizeof(struct Process));
	// display_results(sorted, size);
	insertion_sort(sorted, size);
	
	for(int i=0; i<size; ++i)
	{
		for(int j=i+1; j<size; ++j)
		{
			sorted[j].waiting_time += sorted[i].burst_time;
		}
		sorted[i].turn_around_time = sorted[i].waiting_time + sorted[i].burst_time;
	}
	
	for(int i=0; i<size; ++i)
	{
		for(int j=0; j<size; ++j)
		{
			if(processes[i].process_id == sorted[j].process_id)
			{
				processes[i] = sorted[j];
			}
		}
	}
	display_results(processes, size);
	free(sorted);
}

int main()
{
	printf("Enter the number of processes: ");
	int size;
	scanf("%d", &size);
	struct Process *processes = (struct Process *)calloc(size, sizeof(struct Process));
	
	for(int i=0; i<size; ++i)
	{
		printf("Enter the burst time of process %d: ", i);
		scanf("%d", &processes[i].burst_time);
		
		processes[i].process_id = i;
		processes[i].waiting_time = 0;
		processes[i].turn_around_time = 0;
	}
	sjf(processes, size);
	free(processes);
	return 0;
}
