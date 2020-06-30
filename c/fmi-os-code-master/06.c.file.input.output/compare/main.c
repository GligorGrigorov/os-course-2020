#include <err.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void min(const char * name)
{
	int fd;
	u_int16_t buf;
	u_int16_t maxInt = 1000;
	if((fd = open(name,O_RDONLY)) == -1)
	{
		err(2,"Can't open file.");
	}
	ssize_t readSize;

	while((readSize = read(fd, &buf, sizeof(buf))) > 0)
	{
		if(buf < maxInt)
		{
			maxInt = buf;

		}
	}
	printf("%d",maxInt);
	close(fd);
}
int main(int argc, char** argv)
{
	if(argc != 3)
	{
		errx(1,"Wrong arg. num");
	}
	if(strcmp("--min",argv[1]) == 0)
	{
		min(argv[2]);
	}
	if(strcmp("--max",argv[1]) == 0)
        {
                
        }
	if(strcmp("--print",argv[1]) == 0)
        {
                
        }

	exit(0);
}
