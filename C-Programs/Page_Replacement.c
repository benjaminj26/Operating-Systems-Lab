#include<stdio.h>
#include<stdlib.h>

void fifo_replacement(int *pages, int len, int buffer_len)
{
	int page_hit = 0;
	int page_miss = 0;
	int buffer[buffer_len];
	int first = 0;
	for(int i=0; i<buffer_len; ++i)
	{
		buffer[i] = -1;
	}

	for(int i=0; i<len; ++i)
	{
		int flag = 0;
		for(int j=0; j<buffer_len; ++j)
		{
			if(buffer[j] == pages[i])
			{
				flag = 1;
				break;
			}
		}
		if(flag == 0)
		{
			page_miss++;
			buffer[first] = pages[i];
			if(first == buffer_len-1)
			{
				first = 0;
			}
			else
			{
				first++;
			}
		}
		else
		{
			page_hit++;
		}
	}

	printf("No of page hits => %d\n", page_hit);
	printf("No of page misses => %d\n", page_miss);
	printf("Hit ratio => %d:%d\n", page_hit, len);
	printf("Miss ratio => %d:%d\n", page_miss, len);
}

void optimal_replacement(int *pages, int len, int buffer_len)
{
	int page_hit = 0;
	int page_miss = 0;
	int buffer[buffer_len];

	for(int i=0; i<buffer_len; ++i)
	{
		buffer[i] = -1;
	}

	for(int i=0; i<len; ++i)
	{
		int flag = 0;
		for(int j=0; j<buffer_len; ++j)
		{
			if(buffer[j] == pages[i])
			{
				flag = 1;
				break;
			}
		}

		if(flag == 0)
		{
			page_miss++;
			int adjacency[buffer_len];

			for(int j=0; j < buffer_len; ++j)
			{
				adjacency[j] = 0;
			}
			int optimal;
			for(int j=0; j < buffer_len; ++j)
			{
				for(int k=i+1; k < len; ++k)
				{
					if(buffer[j] == pages[k])
					{
						adjacency[j] = k-i;
						break;
					}
				}
			}
			optimal = 0;
			for(int j=0; j < buffer_len; ++j)
			{
				if(adjacency[j] == 0)
				{
					optimal = j;
					break;
				}
				else if(adjacency[j] > adjacency[optimal])
				{
					optimal = j;
				}
			}
			buffer[optimal] = pages[i];
		}
		else
		{
			page_hit++;
		}
	}

	printf("No of page hits => %d\n", page_hit);
	printf("No of page misses => %d\n", page_miss);
	printf("Hit ratio => %d:%d\n", page_hit, len);
	printf("Miss ratio => %d:%d\n", page_miss, len);
}

void least_recently_used_replacement(int *pages, int len, int buffer_len)
{
	int page_hit = 0;
	int page_miss = 0;
	int buffer[buffer_len];

	for(int i=0; i < buffer_len; ++i)
	{
		buffer[i] = -1;
	}

	for(int i=0; i < len; ++i)
	{
		int flag = 0;

		for(int j=0; j < buffer_len; ++j)
		{
			if(buffer[j] == pages[i])
			{
				flag = 1;
				break;
			}
		}

		if(flag == 0)
		{
			page_miss++;
			int recent[buffer_len];
			for(int j=0; j < buffer_len; ++j)
			{
				recent[j] = -1;
			}
			int least_recent;

			for(int j=0; j < buffer_len; ++j)
			{
				for(int k=0; k < i; ++k)
				{
					if(buffer[j] == pages[k])
					{
						recent[j] = k;
					}
				}
			}
			least_recent = 0;
			for(int j=0; j < buffer_len; ++j)
			{
				if(recent[j] < recent[least_recent])
				{
					least_recent = j;
				}
			}

			buffer[least_recent] = pages[i];
		}
		else
		{
			page_hit++;
		}
	}

	printf("No of page hits => %d\n", page_hit);
	printf("No of page misses => %d\n", page_miss);
	printf("Hit ratio => %d:%d\n", page_hit, len);
	printf("Miss ratio => %d:%d\n", page_miss, len);
}

void least_frequently_used_replacement(int *pages, int len, int buffer_len)
{
	int buffer[buffer_len];
	int page_hit = 0, page_miss = 0;
	for (int i=0; i < buffer_len; ++i)
	{
		buffer[i] = -1;
	}

	for (int i=0; i < len; ++i)
	{
		int flag = 0;

		for(int j=0; j < buffer_len; ++j)
		{
			if(buffer[j] == pages[i])
			{
				flag = 1;
				break;
			}
		}
		if(flag == 0)
		{
			page_miss++;
			int frequency[buffer_len];
			for(int j=0; j < buffer_len; ++j)
			{
				frequency[j] = 0;
			}
			int least_frequent;

			for(int j=0; j < buffer_len; ++j)
			{
				for(int k=0; k < i; ++k)
				{
					if(buffer[j] == pages[k])
					{
						frequency[j] += 1;
					}
				}
			}
			least_frequent = 0;
			for(int j=0; j < buffer_len; ++j)
			{
				if(frequency[j] < frequency[least_frequent])
				{
					least_frequent = j;
				}
			}

			buffer[least_frequent] = pages[i];
		}
		else
		{
			page_hit++;
		}
	}

	printf("No of page hits => %d\n", page_hit);
	printf("No of page misses => %d\n", page_miss);
	printf("Hit ratio => %d:%d\n", page_hit, len);
	printf("Miss ratio => %d:%d\n", page_miss, len);
}

int main()
{
	int len;
	printf("Enter the number of pages: ");
	scanf("%d", &len);
	int pages[len];
	printf("Enter %d page numbers:\n", len);
	for(int i=0; i<len; ++i)
	{
		scanf("%d", &pages[i]);
	}
	int buffer_len;
	printf("Enter the size of the page buffer: ");
	scanf("%d", &buffer_len);

	int exit_status = 1;
	do
	{
		printf(
			"1.FIFO\n"
			"2.Least Recently Used Replacement\n"
			"3.Least Frequently Used Replacement\n"
			"4.Optimal Replacement"
			"5.Exit\nEnter your choice: "
		);
		int choice;
		scanf("%d", &choice);

		switch(choice)
		{
			case 1:
			{
				fifo_replacement(pages, len, buffer_len);
				break;
			}

			case 2:
			{
				least_recently_used_replacement(pages, len, buffer_len);
				break;
			}

			case 3:
			{
				least_frequently_used_replacement(pages, len, buffer_len);
				break;
			}

			case 4:
			{
				optimal_replacement(pages, len, buffer_len);
				break;
			}

			case 5:
			{
				exit_status = 0;
				break;
			}

			default:
			{
				printf("Invalid Input!!!\n");
			}
		}
		printf("\n");
	}while(exit_status);
	return 0;
}
