#include <fcntl.h>
#include <stdio.h>

int	main(void)
{
	int	fd;

	fd = open("test.c", O_RDONLY);
	printf("%d\n", fd);
}


