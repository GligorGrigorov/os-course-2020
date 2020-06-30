#include <err.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
	printf("prompt: ");
	char command[10];
	scanf("%s",command);
	int p[2];
	if(pipe(p) < 0)
	{
		err(2,"error creating pipe");
	}
	int c = fork();
	if(c == 0)
	{
		close(p[0]);
		dup2(p[1],1);
		if(execlp(command,command,(char*)NULL))
		{
			err(1,"error in exec");
		}
	}
	close(p[1]);
	dup2(p[0],0);
	exit(0);
}
