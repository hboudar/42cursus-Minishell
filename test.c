# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <fcntl.h>
# include <errno.h>
# include <sys/types.h>

int main()
{
    int pid;
    int pid1;

    int fd = open("test.txt", O_CREAT | O_RDWR, 0666);

    while (1);

    return (0);
}