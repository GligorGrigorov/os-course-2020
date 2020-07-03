#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <err.h>
#include <stdio.h>
#include <stdint.h>

int cmp(const void* a, const void* b)
{
	return *((uint32_t*) a) - *((uint32_t*) b);
}
int main(int argc, char** argv)
{
	if(argc != 2)
		errx(9,"Wrong number of arguments.");
	int fd1;
	if((fd1 = open(argv[1],O_RDWR)) < 0)
		err(1,"Error opening file %s.", argv[1]);
	struct stat st;
	if(stat(argv[1],&st) < 0)
	{
		int olderrno = errno;
		close(fd1);
		errno = olderrno;
		err(2,"Error stating file %s",argv[2]);
	}
	uint32_t numel = st.st_size / sizeof(uint32_t);  
	if(st.st_size % sizeof(u_int32_t) != 0)
	{
		int olderrno = errno;
		close(fd1);
		errno = olderrno;
		errx(4, "Error in %s structure.",argv[2]);
	}
	if(numel > 100000000)
	{
		int olderrno = errno;
		close(fd1);
		errno = olderrno;
		errx(3, "File %s is too large.",argv[2]);
	}
	if(st.st_size == 0)
	{	
		int olderrno = errno;
		close(fd1);
		errno = olderrno;
		errx(5, "File %s is empty.", argv[1]);
	}
	uint32_t half = numel/2;
	void* buf = malloc(half*sizeof(uint32_t));
	if(!buf)
	{
		err(19,"Error in malloc.");
	}
	uint32_t readSize = 0;
	if((readSize = read(fd1,buf,half*sizeof(uint32_t))) != half*sizeof(uint32_t))
	{
		int olderrno = errno;
		close(fd1);
		errno = olderrno;
		err(6, "Error while reading from file %s", argv[1]);
	}
	int fdTemp;
	if((fdTemp = open("f1.temp", O_CREAT| O_TRUNC| O_RDWR, S_IWUSR| S_IRUSR)) == -1)
	{
		int olderrno = errno;
		close(fd1);
		errno = olderrno;
		err(7, "Error opening file f1.temp");
		
	}
	qsort(buf,half, sizeof(uint32_t),cmp);
	if(write(fdTemp,buf, readSize) == -1)
	{
		int olderrno = errno;
		close(fd1);
		close(fdTemp);
		errno = olderrno;
		err(7, "Error writing to file f1.temp");
	}
	uint32_t readSize2 = 0;
	int fdTemp2;
	if((readSize2 = read(fd1,buf,(numel -half)*sizeof(uint32_t))) != (numel - half)* sizeof(uint32_t))
	{
		int olderrno = errno;
		close(fd1);
		close(fdTemp);
		errno = olderrno;
		err(6, "Error while reading from file %s", argv[1]);
	}
	
	if((fdTemp2 = open("f2.temp", O_CREAT| O_TRUNC| O_RDWR, S_IWUSR| S_IRUSR)) == -1)
	{
		int olderrno = errno;
		close(fd1);
		close(fdTemp);
		errno = olderrno;
		err(7, "Error opening file f2.temp");
	
	}
	qsort(buf, readSize2/sizeof(uint32_t), sizeof(u_int32_t), cmp);
	if(write(fdTemp2, buf, readSize2) == -1)
	{
		int olderrno = errno;
		close(fd1);
		close(fdTemp);
		close(fdTemp2);
		errno = olderrno;
		err(7, "Error writing to file f2.temp");
	}

	lseek(fdTemp,0,SEEK_SET);
	lseek(fdTemp2,0,SEEK_SET);
	lseek(fd1,0,SEEK_SET);
	u_int32_t b1;
	u_int32_t b2;
	//read(fdTemp,&b1, sizeof(u_int32_t));
	//read(fdTemp2,&b2, sizeof(u_int32_t));
	while(read(fdTemp,&b1, sizeof(u_int32_t)) == sizeof(u_int32_t) && read(fdTemp2,&b2, sizeof(u_int32_t)) == sizeof(u_int32_t))
	{
		if(b1 > b2)
		{
			write(fd1,&b2, sizeof(b2));
			lseek(fdTemp, -1 * sizeof(b1), SEEK_CUR);
		}
		else
		{
			write(fd1,&b1, sizeof(b1));
			lseek(fdTemp2, -1 * sizeof(b2), SEEK_CUR);
		}	
	}
	while(read(fdTemp,&b1, sizeof(u_int32_t)) == sizeof(u_int32_t))
	{
		write(fd1,&b1,sizeof(b1));
	}
	while(read(fdTemp2,&b2, sizeof(u_int32_t)) == sizeof(u_int32_t))
	{
		write(fd1,&b2,sizeof(b2));
	}
	int olderrno = errno;
	close(fd1);
	close(fdTemp);
	close(fdTemp2);
	free(buf);
	errno = olderrno;
	
	exit(0);	
}
