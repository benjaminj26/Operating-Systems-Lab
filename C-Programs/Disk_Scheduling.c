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

void sstf(int *positions, int len, int *current, int *total_distance)
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

void insertion_sort(int *array, int size)
{
	for(int i=1; i < size; ++i)
	{
		int key = array[i], j;
		for(j=i-1; j >= 0 && key < array[j]; --j)
		{
			array[j+1] = array[j];
		}
		array[j+1] = key;
	}
}

void scan(int *positions, int len, int *current, int *total_distance, int total_cylinders)
{
	*total_distance = 0;
	int temp[len];
	for(int i=0; i < len; ++i)
	{
		temp[i] = positions[i];
	}
	//Sorting the temp array of positions to make it easier for
	//calculating the distance 
	insertion_sort(temp, len);
	if(*current <= temp[0])
	{
		*total_distance += temp[len - 1] - *current;
	}
	else
	{
		//Distance from current position to the end of the disk
		*total_distance += total_cylinders - 1 - *current;
		//Distance from end of the disk to the position at the other
		//end of the disk
		*total_distance += total_cylinders - 1 - temp[0];

	}
}

void c_scan(int *positions, int len, int *current, int *total_distance, int total_cylinders)
{
	*total_distance = 0;
	int temp[len];
	for(int i=0; i < len; ++i)
	{
		temp[i] = positions[i];
	}
	insertion_sort(temp, len);
	int starting_index;
	if(*current > temp[len - 1])
	{
		*total_distance += total_cylinders - 1 - *current;
		*total_distance += total_cylinders - 1;
		*total_distance += temp[len - 1];
	}
	else if(*current == temp[len - 1])
	{
		*total_distance += total_cylinders - 1 - *current;
		*total_distance += total_cylinders - 1;
		*total_distance += temp[len - 2];
	}
	else if(*current <= temp[0])
	{
		*total_distance += temp[len - 1] - *current;
	}
	else
	{
		//To find the index of the nearest position to the current position
		//which is before the current position
		for(int i=0; i < len; ++i)
		{
			if(temp[i] > *current)
			{
				break;
			}
			else
			{
				//The index of the nearest postion to the current position 
				//which is before the current position
				starting_index = i;
			}
		}
		//Distance between the current position and the end of the disk
		*total_distance += total_cylinders - 1 - *current;
		//Distance between the two ends of the disk
		*total_distance += total_cylinders - 1;
		//Distance from the beginning of the disk and the nearest position
		//to the current position
		*total_distance += temp[starting_index];
	}
}

void look(int *positions, int len, int *current, int *total_distance, int total_cylinders)
{
	*total_distance = 0;
	int temp[len];
	for(int i=0; i < len; ++i)
	{
		temp[i] = positions[i];
	}
	insertion_sort(temp, len);
	if(*current >= temp[len - 1])
	{
		*total_distance += *current - temp[0];
	}
	else if(*current <= temp[0])
	{
		*total_distance += temp[len - 1] - *current;
	}
	else
	{
		*total_distance += temp[len - 1] - *current;
		*total_distance += temp[len - 1] - temp[0];
	}
}

void c_look(int *positions, int len, int *current, int *total_distance, int total_cylinders)
{
	*total_distance = 0;
	int temp[len];
	for(int i=0; i < len; ++i)
	{
		temp[i] = positions[i];
	}
	insertion_sort(temp, len);
	if(*current >= temp[len - 1])
	{
		*total_distance += *current - temp[0];
		*total_distance += temp[len - 1] - temp[0];
	}
	else if(*current <= temp[0])
	{
		*total_distance += temp[len - 1] - *current;
	}
	else
	{
		int starting_index;
		for(int i=0; i < len; ++i)
		{
			if(temp[i] > *current)
			{
				break;
			}
			else
			{
				starting_index = i;
			}
		}
		*total_distance += temp[len - 1] - *current;
		*total_distance += temp[len - 1] - temp[0];
		*total_distance += temp[starting_index] - temp[0];
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
			"2.SSTF\n"
			"3.Scan\n"
			"4.C-Scan\n"
			"5.Look\n"
			"6.C-Look\n"
			"7.Exit\n"
			"Enter your choice: "
		);
		int option;
		scanf("%d", &option);
		
		switch(option)
		{
			case 1:
			{
				current_position = initial_position;
				fcfs(positions, len, &current_position, &total_distance);
				printf("Total Distance: %d\n", total_distance);
				break;
			}
			
			case 2:
			{
				current_position = initial_position;
				sstf(positions, len, &current_position, &total_distance);
				printf("Total Distance: %d\n", total_distance);
				break;
			}

			case 3:
			{
				printf("Enter the total number of cylinders: ");
				int total_cylinders;
				scanf("%d", &total_cylinders);
				current_position = initial_position;
				scan(positions, len, &current_position, &total_distance, total_cylinders);
				printf("Total Distance: %d\n", total_distance);
				break;
			}

			case 4:
			{
				printf("Enter the total number of cylinders: ");
				int total_cylinders;
				scanf("%d", &total_cylinders);
				current_position = initial_position;
				c_scan(positions, len, &current_position, &total_distance, total_cylinders);
				printf("Total Distance: %d\n", total_distance);
				break;
			}

			case 5:
			{
				printf("Enter the total number of cylinders: ");
				int total_cylinders;
				scanf("%d", &total_cylinders);
				current_position = initial_position;
				look(positions, len, &current_position, &total_distance, total_cylinders);
				printf("Total Distance: %d\n", total_distance);
				break;
			}

			case 6:
			{
				printf("Enter the total number of cylinders: ");
				int total_cylinders;
				scanf("%d", &total_cylinders);
				current_position = initial_position;
				c_look(positions, len, &current_position, &total_distance, total_cylinders);
				printf("Total Distance: %d\n", total_distance);
				break;
			}
			
			case 7:
			{
				exit_status = 0;
				break;
			}
			
			default:
			{
				printf("Invalid Input\n");
			}
		}
		printf("\n");
	}while(exit_status);
	return 0;
}