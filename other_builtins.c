#include "headers.h"

//prints what the user enters after the echo command on the console

void echo_x(char **tokens)
{
    int n_str = no_of_strings(tokens);

    // printf("hi\n");
    for (int i = 1; i < n_str; i++)
    {
        printf("%s", tokens[i]);
        printf(" ");
    }
    printf("\n");
}

//prints current working directory
int pwd_x()
{
    char *wd = malloc(150);
    char *x = getcwd(wd, 150);
    if (x == NULL)
    {
        if (errno == EACCES)
        {
            perror("");
            printf("Permission to read or search a component of the filename was denied.\n");
        }
        else if (errno == EINVAL)
        {
            perror("");
            printf("The size argument is zero and buf is not a null pointer\n");
        }
        else if (errno == ENAMETOOLONG)
        {
            perror("");
            printf("The size of the null-terminated absolute pathname string exceeds PATH_MAX bytes.\n");
        }
        else if (errno == ENOMEM)
        {
            perror("");
            printf("Out of memory.\n");
        }
        else if (errno == ERANGE)
        {
            perror("");
            printf("The size argument is less than the length of the absolute pathname of the working directory, including the terminating null byte.  You need to allocate a bigger array and try again.\n");
        }
    }
    printf("%s\n", wd);
    return 0;
}

int history()
{
}
