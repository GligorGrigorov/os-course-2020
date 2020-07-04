#include <stdlib.h>
#include <unistd.h>
#include <err.h>
int main(int argc, char ** argv)
{
	if(argc != 2)
	{
		errx(1, "Wrong number of arguments.");
	}
	int fd[2];
	if(pipe(fd) < 0)
	{
		err(2,"Error creating pipe.");
	}	
	int pid = fork();
	if(pid == 0)
	{
		close(fd[1]);
		dup2(fd[0],0); // error handling
		if(execlp("sort","sort",NULL) < 0)
		{
			close(fd[0]);
			err(3,"Error in execl 1");
		}
		
	}
	close(fd[0]);
	dup2(fd[1],1); // error handling
	if(execlp("cat","cat",argv[1],NULL) < 0)
	{
		close(fd[1]);
		err(4,"Error in execl 2");
	}
	exit(0);	
}
