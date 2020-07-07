#include <err.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys/wait.h>
#include <string.h>
int main()
{
	while(1)
	{
		write(1,"prompt> ",9);
		char readbuf[100];
		int8_t readSize;
		if((readSize = read(0,readbuf,sizeof(readbuf))) < 0)
			err(2, "Error reading from STDIN");
		readbuf[readSize - 1] = '\0';
		if(strcmp("exit",readbuf) == 0)
			exit(0);
		int pid = fork();
		if(pid < 0)
			err(1,"Error in fork.");
		if(pid == 0)
		{
			if(execlp(readbuf,readbuf,0) < 0)
				err(3, "Error in exec.");
		}
		wait(NULL);
	}
	exit(0);
}
