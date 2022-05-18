#include <stdio.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>
#include<stdlib.h>

int main()
{
    int pid;
	pid = getpid();
	printf("The pid of the current process is %d\n", pid);
	if((pid = fork()) == 0)
	{
		printf("New child process started\n");
		for(int i=0; i<10; ++i)
		{
			printf("Hello from child node\n");
		}
	}
	else if(pid < 0)
	{
		printf("Unable to start child process\n");
	}
	else
	{
		wait(NULL);
		printf("Parent process currently executing\n");
	}
	printf("Exiting........\n");
    return 0;
}
