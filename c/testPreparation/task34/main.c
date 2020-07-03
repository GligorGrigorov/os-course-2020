#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdint.h>
#include <errno.h>
#include <fcntl.h>
#include <err.h>
int main(int argc, char** argv)
{
	if(argc != 5)
	{	
		err(1,"Wrong number of arguments.");
	}
	struct stat st;
	if(stat(argv[2],&st) < 0)
	{
		err(2, "Error stating file %s", argv[2]);
	}
	struct idx
	{
		uint16_t offset;
		uint8_t length;
		uint8_t reserved = 0;
	};
	if(st.st_size % sizeof(struct idx) != 0)
	{
		err(3,"Error in %s structure.", argv[2]);
	}
	int fd1dat,fd1idx,fd2dat,fd2idx;
	if((fd1dat= open(argv[1],O_RDONLY)) < 0)
	{
		err(4,"Error opening file %s.", argv[1]);	
	}
	if((fd1idx= open(argv[2],O_RDONLY)) < 0)
	{
		int olderrno = errno;
		close(fd1dat);
		errno = olderrno;
		err(5,"Error opening file %s.", argv[2]);	
	}
	if((fd2dat= open(argv[3],O_CREAT| O_TRUNC|O_WRONLY, S_IWUSR | S_IRUSR)) < 0)
	{
		int olderrno = errno;
		close(fd1dat);
		close(fd1idx);
		errno = olderrno;
		err(6,"Error opening file %s.", argv[3]);	
	}
	if((fd2idx= open(argv[4],O_CREAT| O_TRUNC|O_WRONLY, S_IWUSR | S_IRUSR)) < 0)
	{
		int olderrno = errno;
		close(fd1dat);
		close(fd1idx);
		close(fd2dat);
		errno = olderrno;
		err(7,"Error opening file %s.", argv[4]);	
	}
	struct idx i;
	while(read(fd1idx,&i,sizeof(i)) == sizeof(i))
	{
		if(lseek(fd1dat,i.offset,SEEK_SET) < 0)
		{
			int olderrno = errno;
			close(fd1dat);
			close(fd1idx);
			close(fd2dat);
			close(fd2idx);
			errno = olderrno;
			err(8,"Error seek file %s.", argv[1]);	
		}
		char* buf = malloc(i.length);
		if(!buf)
		{
			int olderrno = errno;
			close(fd1dat);
			close(fd1idx);
			close(fd2dat);
			close(fd2idx);
			errno = olderrno;
			err(9,"Error while allocating memory.");	
		}
		if(read(fd1dat,buf,i.length) != i.length)
		{
			int olderrno = errno;
			close(fd1dat);
			close(fd1idx);
			close(fd2dat);
			close(fd2idx);
			free(buf);
			errno = olderrno;
			err(10,"Error reading from file %s", argv[1]);	
		}
		if(buf[0] >= 'A' && buf[0] <= 'Z')
		{
			if(write(fd2dat,buf,i.length) != i.length)
			{
				int olderrno = errno;
				close(fd1dat);
				close(fd1idx);
				close(fd2dat);
				close(fd2idx);
				free(buf);
				errno = olderrno;
				err(11,"Error writing to file %s", argv[3]);	
				
			}
			if(write(fd2idx,&i,sizeof(i)) != sizeof(i))
			{
				int olderrno = errno;
				close(fd1dat);
				close(fd1idx);
				close(fd2dat);
				close(fd2idx);
				free(buf);
				errno = olderrno;
				err(12,"Error writing to file %s", argv[4]);	
			}
			free(buf);
		}
	}
	int olderrno = errno;
	close(fd1dat);
	close(fd1idx);
	close(fd2dat);
	close(fd2idx);
	errno = olderrno;
	exit(0);	
}
