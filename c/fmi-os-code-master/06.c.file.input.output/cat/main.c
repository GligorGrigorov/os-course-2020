#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <err.h>

int main(int argc, char **argv)
{
	if(argc == 1)
	{
		errx(1,"wrong arg. num");
	}
	int i = 1;
	while(i < argc)
	{
		int fd;
		if((fd=open(argv[i],O_RDONLY)) == -1)
		{
			err(2,"%s",argv[i]);
		}
		char c[4096];
		ssize_t readSize;
		while((readSize = read(fd, &c, sizeof(c))))
		{
			if(write(1,&c,readSize) != readSize)
			{
				close(fd);
				err(3,"%s",argv[i]);
			}
		}
		i = i + 1;
	}
}
