#include <err.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
int cmp(const void * a,const void *b)
{
	return *((unsigned char*) a) - *((unsigned char *)b);
}
int main(int argc, char** argv)
{
	if(argc != 3)
	{
		errx(1,"Wrong arg. number");
	}
	printf("1");
	int fd1 = open(argv[1],O_RDONLY);
	if(fd1 < 0)
	{
		err(2,"error opening file %s", argv[1]);
	}
	printf("2");
	struct stat st;
	if(stat(argv[1],&st) == -1)
	{
		close(fd1);
		err(3,"error stating file %s", argv[1]);
	}
	printf("3");
	int fd2 = open(argv[2],O_CREAT| O_TRUNC| O_WRONLY, S_IRUSR| S_IWUSR);
	if(fd2 < 0)
	{	close(fd1);
		err(4,"error opening filr %s",argv[2]);
	}
	printf("4");
	if(st.st_size == 0)
	{
		close(fd1);
		close(fd2);
		exit(0);
	}
	printf("4.1");
	void *buff = malloc(st.st_size);
	if(!buff)
	{
		int olderrno = errno;
		close(fd1);
		close(fd2);
		errno = olderrno;
		err(5,"no memory");
	}
	printf("5");
	if(read(fd1,buff,st.st_size) != st.st_size)
	{
		close(fd1);
		close(fd2);
		err(6,"error while reading from file %s",argv[1]);
	}
	printf("6");
	qsort(buff, st.st_size, 1, cmp);
	if(write(fd2,buff,st.st_size) != st.st_size)
	{
		close(fd1);
		close(fd2);
		err(7,"err. while writing");
	}
	printf("7");
	free(buff);
	close(fd1);
        close(fd2);

	exit(0);

}
