#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

struct Process
{
	int arrival_time;
	int burst_time;
	int waiting_time;
	int turn_around_time;
};

void fcfs(struct Process *processes, int size)
{
	struct Process oldest;
	int i,j;
	float avg_waiting_time = 0;
	float avg_turn_around_time = 0;
	
	for(i=0; i<size; ++i)
	{
		for(j=i+1; j<size; ++j)
		{
			processes[j].waiting_time += processes[i].burst_time;
		}
		if(i != 0)
		{
			processes[i].waiting_time -= processes[i].arrival_time;
		}
		processes[i].turn_around_time = processes[i].waiting_time + processes[i].burst_time;
	}
	
	for(i=0; i<size; ++i)
	{
		avg_waiting_time += processes[i].waiting_time;
		avg_turn_around_time += processes[i].turn_around_time;
	}
	
	avg_waiting_time /= size;
	avg_turn_around_time /= size;
	
	printf("\nProcess Number\t Arrival Time\t Burst Time\t Waiting Time\t Turn Around Time\n");
	for(i=0; i<size; ++i)
	{
		printf("%d\t\t %d\t\t %d\t\t %d\t\t %d\n", i, processes[i].arrival_time, processes[i].burst_time, processes[i].waiting_time, processes[i].turn_around_time);
	}
	printf("Average Waiting Time = %f\n", avg_waiting_time);
	printf("Average Turn Around Time = %f\n", avg_turn_around_time);
}

int main()
{
	printf("Enter the number of processes: ");
	int size;
	scanf("%d", &size);
	struct Process *processes = (struct Process *)calloc(size, sizeof(struct Process));
	
	for(int i=0; i<size; ++i)
	{
		printf("Enter the arrival time of process %d: ", i);
		scanf("%d", &processes[i].arrival_time);
		
		printf("Enter the burst time of process %d: ", i);
		scanf("%d", &processes[i].burst_time);
		
		processes[i].waiting_time = 0;
		processes[i].turn_around_time = 0;
	}
	fcfs(processes, size);
	free(processes);
	return 0;
}
