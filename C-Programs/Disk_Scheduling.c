#include <stdio.h>

void fcfs(int *positions, int len, int *current, int *total_distance)
{
	*total_distance = 0;
	int distance;
	for(int i=0; i < len; ++i)
	{
		if(*current <= positions[i])
		{
			distance = positions[i] - *current;
		}
		else
		{
			distance = *current - positions[i];
		}
		*total_distance += distance;
		*current = positions[i];
	}
}

void sjf(int *positions, int len, int *current, int *total_distance)
{
	*total_distance = 0;
	
	//Distance of each position from the current position
	int distance[len];
	
	//Temporary array for storing the positions
	int temp[len];
	for(int i=0; i < len; ++i)
	{
		temp[i] = positions[i];
	}
	
	for(int i=0; i < len; ++i)
	{
		//Initializing the distance of each position to -1 so that the 
		//distance is -1 for the positions that are already visited
		//and thereby those distances will not be added to the total
		//distance
		for(int j=0; j < len; ++j)
		{
			distance[j] = -1;
		}
		//The distance of a position is calculated only if
		//the position is unvisited
		for(int j=0; j < len; ++j)
		{
			if(temp[j] == -1)
			{
				continue;
			}
			else if(*current <= temp[j])
			{
				distance[j] = temp[j] - *current;
			}
			else
			{
				distance[j] = *current - temp[j];
			}
		}
		int shortest = 0;
		//Finding a position that has not been visited
		while(shortest < len && distance[shortest] == -1)
		{
			shortest++;
		}
		for(int j=0; j < len; ++j)
		{
			//If all the positions have been visited
			if(shortest >= len)
			{
				return;
			}
			//If the j(th) position has already been visited
			else if(distance[j] == -1)
			{
				continue;
			}
			else if(distance[j] < distance[shortest])
			{
				shortest = j;
			}
		}
		//Assigning the shortest position to the current position variable
		*current = temp[shortest];
		//Marking the current shortest position as visited
		temp[shortest] = -1;
		//Adding the current shortest distance to the total distance
		*total_distance += distance[shortest];
	}
}

int main()
{
	printf("Enter the number of positions: ");
	int len;
	scanf("%d", &len);
	int positions[len];
	
	printf("Enter %d positions:\n", len);
	for(int i=0; i < len; ++i)
	{
		scanf("%d", &positions[i]);
	}
	printf("Enter the initial position: ");
	int initial_position, current_position;
	scanf("%d", &initial_position);
	int total_distance;
	current_position = initial_position;
	int exit_status = 1;
	do
	{
		printf("=========Menu=========\n");
		printf(
			"1.FCFS\n"
			"2.SJF\n"
			"3.Exit\n"
			"Enter your choice: "
		);
		int option;
		scanf("%d", &option);
		
		switch(option)
		{
			case 1:
			{
				total_distance = 0;
				current_position = initial_position;
				fcfs(positions, len, &current_position, &total_distance);
				printf("Total Distance: %d\n", total_distance);
				break;
			}
			
			case 2:
			{
				total_distance = 0;
				current_position = initial_position;
				sjf(positions, len, &current_position, &total_distance);
				printf("Total Distance: %d\n", total_distance);
				break;
			}
			
			case 3:
			{
				exit_status = 0;
				break;
			}
			
			default:
			{
				printf("Invalid Input\n");
			}
		}
	}while(exit_status);
	return 0;
}
