#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <err.h>
int main()
{
	int fd1,fd2,fd3;
	if((fd1 = open("f1",O_RDONLY)) == -1)
	{
		err(1, "Error opening file f1.");
	}
	struct stat st;
	if(stat("f1",&st) < 0)
	{	
		int olderrno = errno;
		close(fd1);
		errno = olderrno;
		err(2,"Error stating file f1.");
	}
	if(st.st_size == 0)
	{
		int olderrno = errno;
		close(fd1);
		errno = olderrno;
		errx(3,"File f1 is empty.");
	}
	if(st.st_size % (2 * sizeof(u_int32_t)) != 0)
	{
		errx(4, "Error in f1 structure.");
	}
	if((fd2 = open("f2",O_RDONLY)) == -1)
	{
		err(5, "Error opening file f2.");
	}
	struct stat st2;
	if(stat("f2",&st2) < 0)
	{	
		int olderrno = errno;
		close(fd1);
		close(fd2);
		errno = olderrno;
		err(6,"Error stating file f2.");
	}
	if(st2.st_size == 0)
	{
		int olderrno = errno;
		close(fd1);
		close(fd2);
		errno = olderrno;
		errx(7,"File f2 is empty.");
	}
	if((fd3 = open("f3",O_CREAT|O_TRUNC|O_WRONLY, S_IWUSR| S_IRUSR)) < 0)
	{
		int olderrno = errno;
		close(fd1);
		close(fd2);
		errno = olderrno;
		err(8,"Error opening file f3.");
		
	}
	struct readBuffer
	{
		u_int32_t x;
		u_int32_t y;
	};
	
	struct readBuffer buf;
	while(read(fd1,&buf,sizeof(buf)) == sizeof(buf))
	{
		if(lseek(fd2,buf.x,SEEK_SET) != buf.x)
		{
			int olderrno = errno;
			close(fd1);
			close(fd2);
			close(fd3);
			errno = olderrno;
			err(9,"Segmentation faulT.");
		}
		void* buffer = malloc(buf.y * sizeof(u_int32_t));
		if(read(fd2,buffer,buf.y) != buf.y)
		{
			int olderrno = errno;
			close(fd1);
			close(fd2);
			close(fd3);
			errno = olderrno;
			err(10,"Error reading from file f2.");
		}
		write(fd3,buffer,buf.y);
		free(buffer);
	}
	lseek(fd1,0,SEEK_SET);
	lseek(fd2,0,SEEK_SET);
	lseek(fd3,0,SEEK_SET);
	close(fd1);
	close(fd2);
	close(fd3);
	exit(0);
}
