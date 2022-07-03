#include<stdio.h>

int buffer=0;
int empty=0;
int full=0;

void wait(int s)
{
	while(s <= 0);
	
	s--;
}

void signal(int s)
{
	s++;
}

void producer(int s, int size)
{
	wait(s);
	
	if(full == size)
	{
		printf("Buffer is full\n");
		signal(s);
		return;
	}
	
	if(empty != 0)
	{
		empty--;
		full++;
		buffer++;
		printf("Item added to buffer\nNumber of items in the buffer: %d\n", buffer);
	}
	
	signal(s);
}

void consumer(int s)
{
	wait(s);
	
	if(empty >= 0)
	{
		if(buffer > 0)
		{
			empty++;
			full--;
			buffer--;
			printf("Item removed from buffer\nNumber of items in buffer: %d\n", buffer);			
		}
		else
		{
			printf("Buffer is empty\n");
		}
	}
	
	signal(s);
}

int main()
{
	printf("Enter the number of slots: ");
	int size;
	scanf("%d", &size);
	empty = size;
	int s=1;
	int status = 1;
	
	do
	{
		printf(
			"=================Menu================\n"
			"1.Call Producer\n"
			"2.Call Consumer\n"
			"3.Exit\n"
			"Enter your choice: "
		);
		
		int choice;
		scanf("%d", &choice);
		
		switch(choice)
		{
			case 1:
			{
				producer(s, size);
				break;
			}
			
			case 2:
			{
				consumer(s);
				break;
			}
			
			case 3:
			{
				printf("Exiting Manufacturing\n");
				status = 0;
				break;
			}
			
			default:
			{
				printf("Invalid Choice\n");
			}
		}
		
		printf("\n");
	}while(status == 1);
	
	return 0;
}
