// копирайте съдържанието на файл1 във файл2
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>

int main(int argc, char* argv[])
//int main()
{
	int fd1;
	int fd2;
	char c;
	
	if(argc != 3)
	{
 		printf("Wrong arg. num.");
		exit(1);
	}

	if ( ( fd1 = open(argv[1], O_RDONLY) ) == -1 ) {
		write(2, "File failed to open in read mode\n", 33);
		exit(-1);
	}

	if ( ( fd2 = open(argv[2], O_CREAT|O_WRONLY, S_IRWXU) ) == -1 ){
		write(2, "File failed to open in write mode\n", 34);
		close(fd1);
		exit(-1);
	}

	while ( read(fd1, &c, 1) ){
		write(fd2, &c, 1);
	}

	close(fd1);
	close(fd2);
	exit(0);
}
