#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <err.h>
int main(int argc, char** argv)
{
	if(argc != 2)
		errx(1,"wrong arg. num.");

	int p[2];
	if(pipe(p) < 0)
		err(2,"cannot create pipe.");

	int c = fork();
	if(c == 0)
	{
		close(p[0]);
		if(dup2(p[1],1) == -1)
		{
			err(8,"dup error");
		}
		if(execlp("cat","cat",argv[1],(char*)NULL) == -1)
		{
			//close(p[0]);
			close(p[1]);
			err(3,"error in execlp");
		}
	}
	close(p[1]);
	dup2(p[0],0);
	
	if(execlp("sort","sort",(char*)NULL) == -1)
	{
		//close(p[0]);
		close(p[0]);
		err(3,"error in execlp");
	}
	exit(0);
}
