#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int	main(int ac, char *av[], char *env[])
{
    char *oldpwd;
    char *pwd;

    oldpwd = getcwd(NULL, 0);
    printf("oldpwd: %s\n", oldpwd);
    if (chdir(av[1]) == 0)
    {
        pwd = getcwd(NULL, 0);
        printf("pwd: %s\n", pwd);
    }
    return 0;
}

