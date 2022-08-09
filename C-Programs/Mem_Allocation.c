#include <stdio.h>
#include <string.h>

enum Status
{
	pending,
	finished
};

enum Result
{
	error,
	success
};

struct Process
{
	int p_id;
	int mem_requirement;
	int allocated_block;
	int remaining_size;
	enum Status status;
};

struct Block
{
	int total_size;
	int remaining_size;
};

void read_processes(struct Process *processes, int proc_len)
{
	printf("\n========Processes========\n");
	for(int i=0; i < proc_len; ++i)
	{
		processes[i].p_id = i+1;
		printf("Enter the memory requirement of process%d: ", processes[i].p_id);
		scanf("%d", &processes[i].mem_requirement);
		processes[i].status = pending;
	}
}

void read_blocks(struct Block *blocks, int block_len)
{
	printf("\n========Memory Blocks========\n");
	for(int i=0; i < block_len; ++i)
	{
		printf("Enter the size of block%d: ", i+1);
		scanf("%d", &blocks[i].total_size);
		blocks[i].remaining_size = blocks[i].total_size;
	}
}

enum Result first_fit(struct Process *processes, int proc_len, struct Block *blocks, int block_len)
{
	for(int i=0; i<proc_len; ++i)
	{
		if(processes[i].status == finished)
		{
			continue;
		}
		else
		{
			for(int j=0; j<block_len; ++j)
			{
				if(processes[i].mem_requirement <= blocks[j].remaining_size)
				{
					blocks[j].remaining_size -= processes[i].mem_requirement;
					processes[i].allocated_block = j;
					processes[i].remaining_size = blocks[j].remaining_size;
					processes[i].status = finished;
					break;
				}
			}
			if(processes[i].status == pending)
			{
				printf("No memory block is big enough for Process%d\n", processes[i].p_id);
				return error;
			}
		}
	}
	return success;
}

enum Result best_fit(struct Process *processes, int proc_len, struct Block *blocks, int block_len)
{
	for(int i=0; i<proc_len; ++i)
	{
		if(processes[i].status == finished)
		{
			continue;
		}
		int best_fit = -1;
		for(int j=0; j<block_len; ++j)
		{
			if(processes[i].mem_requirement <= blocks[j].remaining_size)
			{
				if(best_fit == -1)
				{
					best_fit = j;				
				}
				else
				{
					if(blocks[j].remaining_size < blocks[best_fit].remaining_size)
					{
						best_fit = j;
					}
				}
			}
		}
		if(best_fit == -1)
		{
			printf("No memory block is big enough for Process%d\n", processes[i].p_id);
			return error;
		}
		
		blocks[best_fit].remaining_size -= processes[i].mem_requirement;
		processes[i].remaining_size = blocks[best_fit].remaining_size;
		processes[i].allocated_block = best_fit;
		processes[i].status = finished;
	}
	return success;
}

enum Result worst_fit(struct Process *processes, int proc_len, struct Block *blocks, int block_len)
{
	for(int i=0; i<proc_len; ++i)
	{
		if(processes[i].status == finished)
		{
			continue;
		}
		int highest = 0;
		for(int j=1; j<block_len; ++j)
		{
			if(blocks[j].remaining_size > blocks[highest].remaining_size)
			{
				highest = j;
			}
		}
		if(blocks[highest].remaining_size < processes[i].mem_requirement)
		{
			printf("No memory block is large enough for Process%d\n", processes[i].p_id);
			return error;
		}
		else
		{
			blocks[highest].remaining_size -= processes[i].mem_requirement;
			processes[i].allocated_block = highest;
			processes[i].remaining_size = blocks[highest].remaining_size;
			processes[i].status = finished;
		}
	}
	return success;
}

void display_results(struct Process *processes, int proc_len, struct Block *blocks, int block_len)
{
	printf("Process ID\t Memory Required\t Allocated Block\t Memory Remaining in Block\n");
	for(int i=0; i<proc_len; ++i)
	{
		printf("%d\t\t\t", processes[i].p_id);
		printf("%d\t\t\t", processes[i].mem_requirement);
		printf("%d\t\t\t", processes[i].allocated_block+1);
		printf("%d\n", processes[i].remaining_size);
	}
}

int main()
{
	int proc_len, blk_len;
	printf("Enter the number of processes: ");
	scanf("%d", &proc_len);
	
	printf("Enter the number of memory blocks: ");
	scanf("%d", &blk_len);
	
	struct Process processes[proc_len];
	struct Block blocks[blk_len];
	
	read_processes(processes, proc_len);
	read_blocks(blocks, blk_len);
	enum Status flag = pending;
	do
	{
		printf(
			"1.First Fit\n"
			"2.Best Fit\n"
			"3.Worst Fit\n"
			"4.Exit\n"
			"Enter your choice: "
		);
		int choice;
		scanf("%d", &choice);
		
		switch(choice)
		{
			case 1:
			{
				struct Block temp_blocks[blk_len];
				struct Process temp_processes[proc_len];
				
				memmove(temp_processes, processes, proc_len * sizeof(struct Process));
				memmove(temp_blocks, blocks, blk_len * sizeof(struct Block));
				
				enum Result result = first_fit(temp_processes, proc_len, temp_blocks, blk_len);
				if(result == success)
				{
					display_results(temp_processes, proc_len, temp_blocks, blk_len);
				}
				break;
			}
			
			case 2:
			{
				struct Block temp_blocks[blk_len];
				struct Process temp_processes[proc_len];
				
				memmove(&temp_processes, &processes, proc_len * sizeof(struct Process));
				memmove(&temp_blocks, &blocks, blk_len * sizeof(struct Block));
				enum Result result = best_fit(temp_processes, proc_len, temp_blocks, blk_len);
				if(result == success)
				{
					display_results(temp_processes, proc_len, temp_blocks, blk_len);
				}
				break;
			}
			
			case 3:
			{
				struct Block temp_blocks[blk_len];
				struct Process temp_processes[proc_len];
				
				memmove(&temp_processes, &processes, proc_len * sizeof(struct Process));
				memmove(&temp_blocks, &blocks, blk_len * sizeof(struct Block));
				enum Result result = worst_fit(temp_processes, proc_len, temp_blocks, blk_len);
				if(result == success)
				{
					display_results(temp_processes, proc_len, temp_blocks, blk_len);
				}
				break;
			}
			
			case 4:
			{
				flag = finished;
				break;
			}
			default:
			{
				printf("Invalid Input\n");
			}
		}
		printf("\n");
	}while(flag == pending);
	
	return 0;
}
