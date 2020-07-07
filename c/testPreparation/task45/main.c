#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <err.h>

int main()
{
	int p[2];
	if(pipe(p) < 0)
		err(1,"Error creating pipe.");
	int pid;
	if((pid = fork()) < 0)
		err(2,"Error in fork.");
	if(pid == 0)
	{
		close(p[0]);
		dup2(p[1],1);
		if(execlp("cat","cat" ,"/etc/passwd", NULL) < 0)
		{
			//close(p[1]);
			err(3,"Error in execlp");
		}
	}
	close(p[1]);
	dup2(p[0],0);
	int p2[2];
	if(pipe(p2) < 0)
		err(4,"Error creating pipe p2");
	if((pid = fork()) < 0)
		err(5, "Error in fork 2");
	if(pid == 0)
	{
		close(p2[0]);
		dup2(p2[1],1);
		if(execlp("cut", "cut", "-d:", "-f7", NULL) < 0)
		{
			//close(p2[1]);	
			err(6, "Error in execlp");
		}
	}
	close(p2[1]);
	dup2(p2[0],0);
	int p3[2];
	if(pipe(p3) < 0)
		err(7,"Error creating pipe p3");
	if((pid = fork()) < 0)
		err(8, "Error in fork 3");
	if(pid == 0)
	{
		close(p3[0]);
		dup2(p3[1],1);
		if(execlp("sort", "sort",NULL) < 0)
		{
			err(9,"Error in execlp");
		}
	}
	close(p3[1]);
	dup2(p3[0],0);
	if(execlp("uniq", "uniq", "-c" ,NULL) < 0)
	{
		err(12,"Error in execlp");
	}
	exit(0);
}
