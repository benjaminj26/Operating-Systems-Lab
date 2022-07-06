#include<stdio.h>
#include<unistd.h>
#include<dirent.h>
int main()
{
	DIR *d;
	struct dirent *de;
	d=opendir(".");
	while(de=readdir(d))
	{
		printf("%s ",de->d_name);
	}
	printf("\n");
	return 0;
}
