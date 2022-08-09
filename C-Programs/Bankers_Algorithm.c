#include<stdio.h>

int finished_check(int *finished, int size)
{
	for(int i=0; i<size; ++i)
	{
		if(finished[i] == 0)
		{
			return 1;
		}
	}
	return 0;
}

int main ()
{
	int p_size;
	int r_size;
	
	printf("Enter the number of processes: ");
	scanf("%d", &p_size);
	
	printf("Enter the number of resources: ");
	scanf("%d", &r_size);
	
	int allocated[p_size][r_size];
	int max[p_size][r_size];
	int available[r_size];
	int need[p_size][r_size];
	
	printf("\n========Enter the details========\n");
	for(int i=0; i < p_size; ++i)
	{
		for(int j=0; j < r_size; ++j)
		{
			printf("Enter the instances of Resource%d allocated to process P%d: ", j+1, i+1);
			scanf("%d", &allocated[i][j]);
			
			printf("Enter the maximum instances of Resource%d required by process P%d: ", j+1, i+1);
			scanf("%d", &max[i][j]);
			need[i][j] = max[i][j] - allocated[i][j];
			printf("\n");
		}
	}
	
	for(int i=0; i<r_size; ++i)
	{
		printf("Enter the number of available instances of resource%d: ", i+1);
		scanf("%d", &available[i]);
	}

	printf("Need Matrix:\n");
	printf("Process ID\t\tResources\n");
	for(int i=0; i < p_size; ++i)
	{
		printf("Process_%d\t\t", i+1);
		for(int j=0; j < r_size; ++j)
		{
			printf("%d  ", need[i][j]);
		}
		printf("\n");
	}
	
	int finished[p_size];
	for(int i=0; i<p_size; ++i)
	{
		finished[i] = 0;	
	}
	
	int sequence[p_size];
	int sequence_counter=0;
	while(finished_check(finished, p_size) == 1)
	{
		for(int i=0; i<p_size; ++i)
		{
			int checker[r_size];
			for(int j=0; j<r_size; ++j)
			{
				checker[j] = 0;
			}
			if(finished[i] == 1)
			{
				continue;
			}
			for(int j=0; j<r_size; ++j)
			{
				if(need[i][j] <= available[j])
				{
					checker[j] = 1;
				}
			}
			if(finished_check(checker, r_size) == 0)
			{
				finished[i] = 1;
				sequence[sequence_counter] = i;
				sequence_counter++;
				for(int j=0; j<r_size; ++j)
				{
					available[j] += allocated[i][j];
				}
			}
		}
		
		int temp=0;
		for(int i=0; i<p_size; ++i)
		{
			if(finished[i] == 0)
			{
				temp++;
			}
			else
			{
				break;
			}
		}
		if(temp == p_size)
		{
			printf("The system is in deadlock state\n");
			return 0;
		}
	}
	
	printf("The safe sequence is\n");
	for(int i=0; i<p_size; ++i)
	{
		printf("P%d ", sequence[i]);
	}
	printf("\n");
		
	return 0;
}
