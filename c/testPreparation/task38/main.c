#include <unistd.h>
#include <string.h>
#include <stdint.h>
#include <err.h>
#include <stdlib.h>
#include <stdio.h>
int main(int argc, char** argv)
{
	if(argc != 3)
		errx(1,"Wrong number of arguments.");
	
	uint8_t s = 0;
	uint8_t d = 0;
	if(strcmp(argv[1],"-d") == 0)
		d = 1;
	if(strcmp(argv[1],"-s") == 0)
		s = 1;
	char c;
	if(d)
	{
		while(read(0, &c, sizeof(c)) == sizeof(c))
		{
			uint8_t signal = 0;
			uint8_t i = 0;
			while(argv[2][i] != '\0')
			{
				if(argv[2][i] == c)
				{
					signal = 1;
					break;
				}
				i++;
			}
			if(!signal)
			{
				if(write(1,&c,sizeof(c)) < 0)
					err(3, "Error writing to STDOUT");
			}
		}
		exit(0);
	}
	if(s)
	{
		if(read(0,&c,sizeof(c)) != sizeof(c))
			errx(4, "Error reading from STDIN");
		char c1;
		while(read(0, &c1, sizeof(c1)) == sizeof(c1))
		{
			write(1, &c, sizeof(c)); //err
			uint8_t i = 0;
			uint8_t signal = 0;	
			while(argv[2][i] != '\0')
			{
				if(argv[2][i] == c1)
				{
					signal = 1;
					break;
				}
				i++;
			}
			while(c == c1 && signal)
			{
				if(read(0, &c1, sizeof(c1)) != sizeof(c1) )
				{
					err(5, "Error reading from STDIN");
				}
			}
			c = c1;
		}
		exit(0);	
	}
	if(strlen(argv[1]) != strlen(argv[2]))
		errx(6,"SET1 and SET2 have diffenrent sizes.");
	
	while(read(0,&c, sizeof(c)) == sizeof(c))
	{	
		uint8_t i = 0;
		uint8_t signal = 0;
		while(argv[1][i] != '\0')
		{
			if(argv[1][i] == c)
			{
				signal = 1;
				break;
			}
			i++;
		}
		if(signal)
			c = argv[2][i];
		write(1,&c,sizeof(c)); //err
	}
	
	exit(0);
}
