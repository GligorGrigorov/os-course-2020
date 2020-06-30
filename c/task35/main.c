#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <err.h>
#include <stdlib.h>
#include <stdint.h>
int main(int argc, char** argv)
{
	if(argc != 4)
		errx(1,"wrong argument number.");
	int fd1 = open(argv[1],O_RDONLY);
	if(fd1 < 0)
	{
		err(2,"Error opening file %s",argv[1]);
	}
	int fd2 = open(argv[2],O_RDONLY);
	if(fd2 < 0)
	{
		int olderrno = errno;
		close(fd1);
		errno = olderrno;
		err(3,"Error opening file %s",argv[2]);
	}
	
	struct stat st;
	if(fstat(fd1,&st))
	{
		int olderrno = errno;
		close(fd1);
		close(fd2);
		errno = olderrno;
		err(4,"Error stating file %s",argv[1]);
	}
	int f1Size = st.st_size;
	if(fstat(fd2,&st))
	{
		int olderrno = errno;
		close(fd1);
		close(fd2);
		errno = olderrno;
		err(5,"Error stating file %s",argv[2]);
	}
	int f2Size = st.st_size;
	if(f1Size != f2Size)
	{

		int olderrno = errno;
		close(fd1);
		close(fd2);
		errno = olderrno;
		errx(6,"Difference in files sizes.");
	}

	int fd3 = open(argv[3],O_CREAT|O_TRUNC|O_WRONLY,S_IWUSR|S_IRUSR);
	if(fd3 < 0)
	{
		int olderrno = errno;
		close(fd1);
		close(fd2);
		errno = olderrno;
		err(7,"Error opening file %s",argv[3]);
	}
	struct patch
	{
		uint16_t offset;
		uint8_t original;
		uint8_t new;
	};
	struct patch p;
	uint8_t buf1;
	uint8_t buf2;
	uint16_t counter = 0;
	while(read(fd1,&buf1,sizeof(buf1)) == sizeof(buf1))
	{
		if(read(fd2,&buf2,sizeof(buf2)) != sizeof(buf2))
		{
			int olderrno = errno;
			close(fd1);
			close(fd2);
			close(fd3);
			errno = olderrno;
			err(8,"Error reading from file %s",argv[2]);
		}
		if(buf1 != buf2)
		{
			p.offset = counter;
			p.original = buf1;
			p.new = buf2;
			if(write(fd3,&p,sizeof(p)) != sizeof(p))
			{
				
				int olderrno = errno;
				close(fd1);
				close(fd2);
				close(fd3);
				errno = olderrno;
				err(9,"Error writing to file %s",argv[3]);
			}
		}
		counter++;
		
	}
	close(fd1);
	close(fd2);
	close(fd3);
	exit(0);
}
