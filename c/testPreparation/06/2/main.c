/*
	Реализирайте команда head без опции (т.е. винаги да извежда
	на стандартния изход само първите 10 реда от съдържанието на
	файл подаден като първи параматър)
*/
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <err.h>

int main(int argc, char** argv)
{
	if(argc != 2)
	{
		errx(1, "Wrong number of arguments.");	
	}
	int fd1;
	if((fd1 = open(argv[1],O_RDONLY)) == -1)
		err(2, "Error opening file");
	int lines = 0;
	char buf;
	int size;
	while((size = read(fd1, &buf, sizeof(buf))) > 0 && lines != 10)
	{
		if((write(1, &buf, size)) == -1)
		{
			int olderrno = errno;
			close(fd1);
			errno = olderrno;
			err(3, "Error writing to STDOUT.");
			
		}
		if(buf == '\n')
			lines++;
	}
	close(fd1);
	exit(0);
}
