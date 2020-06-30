#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdint.h>
#include <unistd.h>
#include <stdlib.h>
int main()
{	
	struct dat
	{
		uint16_t a;
		uint8_t b;
		uint8_t c;
	};
	struct dat s;
	s.a = 5;
	s.b = 6;
	s.c = 1;

	struct dat* p = &s;
	int fd1;
	fd1 = open("f.dat",O_CREAT|O_WRONLY| O_APPEND, S_IWUSR| S_IRUSR);
	write(fd1,&p->a,sizeof(p->a));
	write(fd1,&p->b,sizeof(p->b));
	write(fd1,&p->c,sizeof(p->c));
	close(fd1);
	exit(0);
}
