#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <err.h>
#include <stdint.h>

struct pair
{
	u_int32_t position;
	u_int32_t offset;

};

int main()
{
	int fd1 = open("f1",O_RDONLY);
	if(fd1 < 0)
	{
		err(1,"error opening file f1");
	}
	int fd2 = open("f2",O_RDONLY);
	if(fd2 < 0)
	{
		err(2,"error opening file f2");
	}
	struct stat st;
	if(stat("f1",&st) == -1)
	{	
		close(fd1);
		close(fd2);
		err(3,"error stat file f1");
	}

	if(st.st_size % sizeof(struct pair) != 0)
	{
		errx(4,"error in file pairs");
	}
	struct stat st2;
	if(stat("f2", &st2) == -1)
	{
		close(fd1);
		close(fd2);
		err(5,"error stat file f2");
	}
	int fd3;
	if((fd3 = open("f3",O_CREAT |O_TRUNC | O_WRONLY,S_IWUSR | S_IRUSR)) == -1)
	{
		err(8,"error opening file f3");
	}
	struct pair p;
	uint32_t readBuf;
	while(read(fd1, &p, sizeof(p)) == sizeof(p))
	{
		lseek(fd2,p.position * sizeof(uint32_t),SEEK_SET);
		uint32_t counter = 0;
	//	if(counter == p.offset)
	//	{
	//		break;
	//	}

		while(counter != p.offset)
		{
			if(read(fd2,&readBuf,sizeof(readBuf)) == sizeof(readBuf))
			{
				if(write(fd3, &readBuf,sizeof(readBuf)) != sizeof(readBuf))
				{
					err(5,"error writing to file f3");
				}
			}
		}
		lseek(fd2,0,SEEK_SET);
		counter++;
	}
		
	exit(0);
}
