#include <err.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <err.h>
#include <stdio.h>
int cmp(const void * a, const void * b)
{
	return *((unsigned char*)a) - *((unsigned char*)b);
}

int main(int argc, char** argv)
{
	if(argc != 2)
	{
		errx(1, "Wrong number of args.");
	}
	int fd;
	if((fd = open(argv[1],O_RDWR)) == -1)
	{
		err(2, "Error opening file %s.", argv[1]);
	}
	struct stat st;
	if(stat(argv[1],&st) < 0)
	{
		int olderrno = errno;
		close(fd);
		errno = olderrno;
		err(3, "Error stating file %s", argv[1]);
	}
	if(st.st_size == 0)
	{	
		int olderrno = errno;
		close(fd);
		errno = olderrno;
		errx(4, "File %s is empty.", argv[1]);
	}
	void* buf = malloc(st.st_size);
	if(buf == NULL)
	{
		int olderrno = errno;
		free(buf);
		close(fd);
		errno = olderrno;
		err(5, "No memory");
	}
	if(read(fd, buf,st.st_size) != st.st_size)
	{
		int olderrno = errno;
		free(buf);
		close(fd);
		errno = olderrno;
		err(6, "Error reading from file %s", argv[1]);
	}
	qsort(buf,st.st_size,1,cmp);
	lseek(fd,0,SEEK_SET);
	if(write(fd, buf,st.st_size) != st.st_size)
	{
		int olderrno = errno;
		free(buf);
		close(fd);
		errno = olderrno;
		err(7, "Error writing to file %s", argv[1]);
	
	}
	free(buf);
	close(fd);
	exit(0);	
}

