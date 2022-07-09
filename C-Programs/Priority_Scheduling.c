#include <stdio.h>
#include <stdlib.h>

enum Status
{
	finished,
	pending
};

struct Process
{
	unsigned p_id;
	unsigned burst_time;
	unsigned priority;
	unsigned waiting_time;
	unsigned turn_around_time;
	enum Status status;
};

void read_processes(struct Process *processes, unsigned size)
{
	for(unsigned i=0; i<size; ++i)
	{
		processes[i].p_id = i+1;
		printf("Enter the burst time of Process%d: ", processes[i].p_id);
		scanf("%u", &processes[i].burst_time);
		printf("Enter the priority of Process%d: ", processes[i].p_id);
		scanf("%u", &processes[i].priority);
		processes[i].waiting_time = 0;
		processes[i].turn_around_time = 0;
		processes[i].status = pending;
	}
}

void display_results(struct Process *processes, unsigned size)
{
	float avg_waiting_time=0;
	float avg_turn_around_time=0;
	printf
	(
		"Process ID\t"
		"Burst Time\t"
		"Priority\t"
		"Waiting Time\t"
		"Turn Around Time\n"
	);
	for(unsigned i=0; i<size; ++i)
	{
		printf("%u\t\t",processes[i].p_id);
		printf("%u\t\t",processes[i].burst_time);
		printf("%u\t\t",processes[i].priority);
		printf("%u\t\t",processes[i].waiting_time);
		printf("%u\n",processes[i].turn_around_time);
		avg_waiting_time += processes[i].waiting_time;
		avg_turn_around_time += processes[i].turn_around_time;
	}
	avg_waiting_time /= size;
	avg_turn_around_time /= size;

	printf("Average Waiting Time is %f\n", avg_waiting_time);
	printf("Average Turn Around Time is %f\n", avg_turn_around_time);
}

void priority_scheduling(struct Process *processes, unsigned size)
{
	for(unsigned i=0; i<size; ++i)
	{
		unsigned highest = 0;
		for(unsigned j=0; j<size; ++j)
		{
			if(processes[j].priority > processes[highest].priority && processes[j].status == pending)
			{
				highest = j;
			}
		}
		for(unsigned j=0; j<size; ++j)
		{
			if(j != highest && processes[j].status == pending)
			{
				processes[j].waiting_time += processes[highest].burst_time;
			}
		}
		processes[highest].status = finished;
	}

	for(unsigned i=0; i<size; ++i)
	{
		processes[i].turn_around_time = processes[i].waiting_time + processes[i].burst_time;
	}
}

int main()
{
	unsigned size;
	printf("Enter the number of processes: ");
	scanf("%u", &size);
	struct Process *processes = (struct Process*)calloc(size, sizeof(struct Process));
	read_processes(processes, size);
	priority_scheduling(processes, size);
	display_results(processes, size);
	free(processes);
	return 0;
}