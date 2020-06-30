#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <err.h>

int main(int argc, char** argv)
{
	int fd1;
	char c;
	int counter = 0;

	if(argc != 2)
	{
		errx(-2,"err");
		exit(-2);
	}
	if( (fd1=open(argv[1],O_RDONLY)) == -1)
	{
		errx(-1,"Can't open file.");
		exit(-1);
	}
	while(read(fd1,&c,sizeof(c)))
	{
		if(c == '\n')
		{
			counter = counter + 1;
		}
		write(1,&c,sizeof(c));
		if(counter == 10)
		{
			break;
		}
	}
	close(fd1);
	exit(0);
}
