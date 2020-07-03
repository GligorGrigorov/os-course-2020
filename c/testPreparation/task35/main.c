#include <stdlib.h>
#include <err.h>
#include <errno.h>
#include <stdint.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>


int main(int argc, char** argv)
{
	if(argc != 4)
	{
		errx(1,"Wrong number of arguments.");
	}
	struct stat st1;
	struct stat st2;
	if(stat(argv[1],&st1) < 0)
	{
		err(2,"Error stating file %s", argv[1]);
	}
	if(stat(argv[2],&st2) < 0)
	{
		err(3,"Error stating file %s", argv[2]);
	}
	if(st1.st_size != st2.st_size)
	{
		errx(4,"Files %s and %s have different sizes.",argv[1], argv[2]);
	}
	int fd1,fd2,fdp;
	if((fd1 = open(argv[1],O_RDONLY)) < 0)
	{
		err(5,"Error opening file %s", argv[1]);
	}
	if((fd2 = open(argv[2],O_RDONLY)) < 0)
	{	
		int olderrno = errno;
		close(fd1);
		errno = olderrno;
		err(6,"Error opening file %s", argv[2]);
	}
	if((fdp = open(argv[3],O_CREAT | O_TRUNC | O_WRONLY, S_IWUSR | S_IRUSR)) < 0)
	{	
		int olderrno = errno;
		close(fd1);
		close(fd2);
		errno = olderrno;
		err(7,"Error opening file %s", argv[3]);
	}
	struct patch
	{
		uint16_t offset;
		uint8_t original;
		uint8_t new;
	};
	struct patch p;
	int offset = 0;
	while(read(fd1,&p.original,sizeof(p.original)) == sizeof(p.original))
	{
		if(read(fd2,&p.new,sizeof(p.new)) != sizeof(p.new))
		{
			int olderrno = errno;
			close(fd1);
			close(fd2);
			close(fdp);
			errno = olderrno;
			err(8,"Error reading from file %s", argv[2]);
		}
		
		if(p.original != p.new)
		{
			p.offset = offset;
			if(write(fdp,&p,sizeof(p)) != sizeof(p))
			{
				int olderrno = errno;
				close(fd1);
				close(fd2);
				close(fdp);
				errno = olderrno;
				err(9,"Error writing to file %s", argv[3]);
			}	
		}
		offset++;
	}
	close(fd1);
	close(fd2);
	close(fdp);
	exit(0);
}
