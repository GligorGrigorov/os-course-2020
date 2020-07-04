#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdint.h>
#include <err.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

uint8_t addNumbers = 0;
uint32_t line = 1;

void cat(int fd)
{
	char buf;
	uint8_t newline = 1;
	while(read(fd, &buf, sizeof(buf)) == sizeof(buf))
	{
		setbuf(stdout, NULL);
		if(addNumbers && newline)
		{
			printf("%d ",line);
			line++;
			newline = 0;
		}
		if(write(1,&buf,sizeof(buf)) != sizeof(buf))
		{
			err(2,"Error writing...");
		}
		if(buf == '\n')
			newline = 1;
	}
}

int main(int argc, char** argv)
{
	if(argc == 1)
	{
		cat(0);
		exit(0);
	}
	int i = 1;
	if(strcmp(argv[i],"-n") == 0)
	{
		addNumbers = 1;
		i++;
	}
	for(;i < argc;i++)
	{
		if(strcmp(argv[i],"-") == 0)
		{
			cat(0);
		}
		else
		{
			int fd;
			if((fd = open(argv[i],O_RDONLY)) < 0)
			{
				err(1,"Error opening file %s", argv[i]);
			}
			cat(fd);
			close(fd);
		}
	}
	exit(0);
}
