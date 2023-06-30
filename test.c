#include <stdio.h>
#include <fcntl.h>

int main()
{
    int fd = open("test.c", O_RDONLY);
    printf("%d\n", fd);
}
