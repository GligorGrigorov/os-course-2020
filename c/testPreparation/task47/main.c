#include <unistd.h>
#include <err.h>
#include <sys/types.h>

int main(int argc, char** argv)
{
	if(argc != 2)
		errx(1,"Wrong number of arguments.");
	int p1[2];
	if(pipe(p1) < 0)
		err(2,"Error creating pipe."); 
	int pid1;
	if((pid1 = fork()) < 0)
		err(3,"Error in fork.");
	if(pid1 == 0)
	{
		close(p1[0]);
		dup2(p1[1],1);
		if(execlp("find","find",argv[1],"-type","f","-printf","%T@ %p\n",NULL) < 0)
		{
			close(p1[1]);
			err(4,"execlp failed.");
		}
		
	}
	close(p1[1]);
	dup2(p1[0],0);
	int p2[2];
	if(pipe(p2) < 0)
		err(5,"Error creating pipe2."); 
	int pid2;
	if((pid2 = fork()) < 0)
		err(6,"Error in fork.");
	if(pid2 == 0)
	{
		close(p2[0]);
		dup2(p2[1],1);
		if(execlp("cut","cut","-d"," ","-f2",NULL) < 0)
		{
			close(p2[1]);
			err(7,"execlp 2 failed.");
		}
	}
	close(p2[1]);
	dup2(p2[0],0);
	if(execlp("head","head","-n","1",NULL) < 0)
	{
		close(p2[0]);
		err(8,"execlp 3 failed.");
	}
}
