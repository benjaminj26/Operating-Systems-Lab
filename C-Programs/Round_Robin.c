#include<stdio.h>
#include<stdlib.h>

struct Process
{
	int p_id;
	int burst_time;
	int time_remaining;
	int waiting_time;
	int turn_around_time;
};

void display(struct Process *processes, int size)
{
	float avg_wt = 0;
	float avg_tat = 0;
	printf("Process ID\t Burst Time\t Waiting Time\t Turn Around Time\n");
	for(int i=0; i<size; ++i)
	{
		printf("%d\t\t %d\t\t %d\t\t %d\n", processes[i].p_id, processes[i].burst_time, processes[i].waiting_time, processes[i].turn_around_time);
		avg_wt += processes[i].waiting_time;
		avg_tat += processes[i].turn_around_time;
	}
	avg_wt = avg_wt/(float)size;
	avg_tat = avg_tat/(float)size;
	
	printf("Average Waiting Time : %f\n", avg_wt);
	printf("Average Turn Around Time : %f\n", avg_tat);
}

int check_remaining_time(struct Process *processes, int size)
{
	int flag[size];
	for(int i=0; i<size; ++i)
	{
		if(processes[i].time_remaining == 0)
		{
			flag[i] = 0;
		}
		else
		{
			return 1;
		}
	}
	return 0;
}

void round_robin(struct Process *processes, int size)
{
	printf("Enter the value of time slice: ");
	int time_slice;	
	scanf("%d", &time_slice);
	
	while(check_remaining_time(processes, size) == 1)
	{
		for(int i=0; i<size; ++i)
		{
			if(processes[i].time_remaining < time_slice)
			{
				int remaining_time = processes[i].time_remaining;
				processes[i].time_remaining -= processes[i].time_remaining;
				for(int j=0; j<size; ++j)
				{
					if(j != i && processes[j].time_remaining != 0)
					{
						processes[j].waiting_time += remaining_time;
					}
				}
			}
			else
			{
				processes[i].time_remaining -= time_slice;
				for(int j=0; j<size; ++j)
				{
					if(j != i && processes[j].time_remaining != 0)
					{
						processes[j].waiting_time += time_slice;
					}
				}
			}
		}
	}
	
	for(int i=0; i<size; ++i)
	{
		processes[i].turn_around_time = processes[i].waiting_time + processes[i].burst_time;
	}
}

int main()
{
	int size;
	printf("Enter the number of processes: ");
	scanf("%d", &size);
	
	struct Process *processes = (struct Process*)calloc(size, sizeof(struct Process));
	
	for(int i=0; i<size; ++i)
	{
		processes[i].p_id = i+1;
		printf("Enter the burst time of process %d: ", processes[i].p_id);
		scanf("%d", &processes[i].burst_time);
		processes[i].time_remaining = processes[i].burst_time;
		processes[i].waiting_time = 0;
		processes[i].turn_around_time = 0;
	}
	round_robin(processes, size);
	display(processes, size);
	return 0;
}
