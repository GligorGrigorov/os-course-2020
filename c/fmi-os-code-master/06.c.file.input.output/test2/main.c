#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <err.h>

int main(int argc, char** argv)
{
	int fd1;
	int fd2;
	if(argc != 3)
	{
		errx(1,"Wrong arg. num.");
	}
	if((fd1=open(argv[1],O_RDONLY)) == -1)
	{
		errx(2,"%s",argv[1]);
	}
	if((fd2=open(argv[2],O_CREAT | O_WRONLY | O_TRUNC,S_IRUSR| S_IWUSR)) == -1)
	{
		close(fd1);
		errx(3,"%s",argv[2]);
	}
	ssize_t readSize;
	char c[4096];
	while((readSize=read(fd1,&c,sizeof(c))) > 0)
	{
		if(write(fd2,&c,readSize) != readSize)
		{
			close(fd1);
			close(fd2);
			errx(4,"error writing to file.");
		}
	}
	close(fd1);
	close(fd2);
}

