#include <unistd.h>
#include <stdint.h>
#include <err.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
int main(int argc, char** argv)
{
	if(argc != 4)
		errx(1,"Wrong number of arguments.");
	struct patch
	{
		uint16_t offset;
		uint8_t original;
		uint8_t new;
	};
	struct stat st;
	if(stat(argv[1],&st) < 0)
		err(2,"Error stating file %s", argv[1]);
	if(st.st_size % sizeof(struct patch) != 0)
		errx(3,"Error in %s structure.", argv[1]);
	int fdp,fd1,fd2;
	if((fdp = open(argv[1],O_RDONLY)) < 0)
		err(4, "Error opening file %s.", argv[1]);
	if((fd1 = open(argv[2],O_RDONLY)) < 0)
	{
		int olderrno = errno;
		close(fdp);
		errno = olderrno;
		err(5,"Error opening file %s.", argv[2]);
	}
	if((fd2 = open(argv[3],O_CREAT | O_TRUNC | O_RDWR, S_IWUSR | S_IRUSR)) < 0)
	{
		int olderrno = errno;
		close(fdp);
		close(fd1);
		errno = olderrno;
		err(6,"Error opening file %s.", argv[3]);
	}
	struct patch p;
	uint8_t buf;
	while(read(fd1,&buf,sizeof(buf)) == sizeof(buf))
	{
		if(write(fd2,&buf,sizeof(buf)) != sizeof(buf))
		{
			int olderrno = errno;
			close(fdp);
			close(fd1);
			close(fd2);
			errno = olderrno;
			err(7,"Error writing to file %s.", argv[3]);
		}
	}
	while(read(fdp,&p, sizeof(p)) == sizeof(p))
	{
		if(lseek(fd1,p.offset,SEEK_SET) < 0 || lseek(fd2,p.offset, SEEK_SET) < 0)
		{
			int olderrno = errno;
			close(fdp);
			close(fd1);
			close(fd2);
			errno = olderrno;
			err(8,"Error in seek of file %s or %s.", argv[2], argv[3]);
		}
		if(read(fd1,&buf,sizeof(buf)) < 0)
		{
			int olderrno = errno;
			close(fdp);
			close(fd1);
			close(fd2);
			errno = olderrno;
			err(9,"Error reading from file %s", argv[2]);
		}	
		if(buf == p.original)
		{
			lseek(fd2,p.offset, SEEK_SET); //err
			write(fd2,&p.new, sizeof(p.new)); //err
		}
	}
	exit(0);
}
