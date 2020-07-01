// копирайте съдържанието на файл1 във файл2
#include <stdlib.h>
#include <err.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char** argv)
{
	if(argc != 3)
		errx(1,"Wrong number of arguments");		
	int fd1;
	if((fd1 = open(argv[1], O_RDONLY)) == -1)
		err(2,"Error opening file %s", argv[1]);	
	
	int fd2;
	if((fd2 = open(argv[2], O_CREAT | O_RDWR | O_TRUNC, S_IRUSR | S_IWUSR )) == -1)
		err(3,"Error opening file %s", argv[2]);
	char buf;
	int size;
	while((size = read(fd1, &buf, sizeof(buf))) > 0)
	{
		if(write(fd2, &buf, size) == -1)
			err(4,"Error writing to file %s", argv[2]);
	}
	close(fd1);
	close(fd2);
	exit(0);
}
