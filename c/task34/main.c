#include <err.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdint.h>
#include <fcntl.h>
#include <errno.h>
int main(int argc,char** argv)
{
	if(argc != 5)
	{
		errx(1,"Wrong arg. num.");
	}
	struct stat st;
	if(stat(argv[2],&st) < 0)
	{
		err(2,"error stat file %s",argv[2]);
	}
	if(st.st_size % (sizeof(uint16_t) + sizeof(uint8_t) + sizeof(uint8_t)) != 0)
	{
		errx(3,"error in %s structure", argv[2]);
	}
	int fdIdx = open(argv[2],O_RDONLY);
	if(fdIdx < 0)
	{
		err(4,"error opening file %s", argv[2]);
	}
	int fdDat = open(argv[1],O_RDONLY);
	if(fdDat < 0)
	{
		int olderrno = errno;
		close(fdIdx);
		errno = olderrno;
		err(5,"error opening file %s", argv[1]);
	}
	
	int fd2Idx = open(argv[4],O_CREAT|O_TRUNC|O_WRONLY, S_IRUSR);
	if(fd2Idx < 0)
	{
		int olderrno = errno;
		close(fdIdx);
		close(fdDat);
		errno = olderrno;
		err(6,"error opening file %s", argv[4]);
	}

	int fd2Dat = open(argv[3],O_CREAT|O_TRUNC|O_WRONLY, S_IRUSR);
	if(fd2Dat < 0)
	{
		int olderrno = errno;
		close(fdIdx);
		close(fdDat);
		close(fd2Idx);
		errno = olderrno;
		err(7,"error opening file %s", argv[3]);
	}
	struct idx
	{
		uint16_t position;
	 	uint8_t length;
		uint8_t skip;
	};
	
	struct idx buf;
	while(read(fdIdx,&buf,sizeof(buf)) == sizeof(buf))
	{
		off_t offset = lseek(fdDat,buf.position,SEEK_SET);
		if(offset < 0)
		{
			int olderrno = errno;
			close(fdIdx);
			close(fdDat);
			close(fd2Idx);
			close(fd2Dat);
			errno = olderrno;
			err(6,"lseek error");
		}
		uint8_t counter = 0;
		uint8_t datBuf;
		while(read(fdDat,&datBuf,sizeof(datBuf)) == sizeof(datBuf))
		{
			if(counter == buf.length)
				break;
			if(counter == 0)
			{
				if(!(datBuf >= 0x41 && datBuf <= 0x5A))
				{
					break;
				}
			}
			if(write(fd2Dat,&datBuf,sizeof(datBuf)) != sizeof(datBuf))
			{
				int olderrno = errno;
				close(fdIdx);
				close(fdDat);
				close(fd2Idx);
				close(fd2Dat);
				errno = olderrno;
				err(9,"error writing to file %s",argv[3]);
			}
			counter++;
		}
		if(write(fd2Idx,&buf,sizeof(buf)) != sizeof(buf))
		{
			
			int olderrno = errno;
			close(fdIdx);
			close(fdDat);
			close(fd2Idx);
			close(fd2Dat);
			errno = olderrno;
			err(10,"error writing to file %s",argv[4]);
		}
	}
	exit(0);
}
