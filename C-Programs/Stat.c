#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdlib.h>

int main()

{
	char *path,path1[10]; 
	struct stat *nfile;
	nfile=(struct stat *) malloc (sizeof(struct stat));
	printf("Enter name of file whose statistics has to be displayed: ");
	scanf("%s",path1);
	stat(path1,nfile);
	printf("user id %u\n", nfile->st_uid);
	printf("block size :%ld\n", nfile->st_blksize);
	printf("last access time %ld\n", nfile->st_atime);
	printf("time of last modification %ld\n", nfile->st_mtime);
	printf("production mode %u\n", nfile->st_mode);
	printf("size of file %ld\n", nfile->st_size);
	printf("number of links:%ld\n", nfile->st_nlink);
	return 0;
}
