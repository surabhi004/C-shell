#include "headers.h"
#include "cd.h"

void pinfo_x(char **tokens)
{
    int n = no_of_strings(tokens);

    pid_t pid;
    if (n == 1)
    {
        pid = getpid();
    }
    else
    {
        pid = atoi(tokens[1]);
    }

    char *filename = malloc(200);
    sprintf(filename, "/proc/%d/stat", pid);
    FILE *f = fopen(filename, "r");
    char *symlink = malloc(200);
    sprintf(symlink, "/proc/%d/exe", pid);
    FILE *f2 = fopen(symlink, "r");
    char *path = malloc(200);
    int e = readlink(symlink, path, 200);
    if (e == -1)
    {
        if (errno == EACCES)
        {
            printf("Search permission is denied for a component of the path prefix\n");
        }
        else if (errno == EFAULT)
        {
            printf("buf extends outside the process's allocated address space\n");
        }
        else if (errno == EINVAL)
        {
            printf("The named file (i.e., the final filename component of pathname) is not a symbolic link");
        }
        else if (errno == EIO)
        {
            printf("An I/O error occurred while reading from the filesystem\n");
        }
        else if (errno == ELOOP)
        {
            printf("Too many symbolic links were encountered in translating the pathname\n");
        }
        else if (errno == ENAMETOOLONG)
        {
            printf("A pathname, or a component of a pathname, was too long\n");
        }
        else if (errno == ENOENT)
        {
            printf("The named file does not exist\n");
        }
        else
        {
            perror("");
        }
    }

    int unused;
    char *buffer = malloc(1000);

    fgets(buffer, 1000, f);

    char *name = malloc(100);
    char **info = tokenize(buffer, " ");
    name = info[1];
    char *state = info[2];
    int ppid;

    char *vsize = malloc(50);
    vsize = info[22];

    int isForeground = 0;
    if (getpgid(pid) == getpgrp())
    {
        //then foreground
        isForeground = 1;
    }
    if (n == 1)
    {
        pid = getpid();
    }
    printf("pid -- %d\n", pid);

    if (isForeground || (strcmp(state, "Z") == 0) || (strcmp(state, "T") == 0))
    {
        printf("Process Status -- %s\n", state);
    }
    else
    {
        printf("Process Status -- %s+\n", state);
    }

    printf("memory -- %s\n", vsize);

    printf("executable path -- %s\n", path);

    fclose(f);
    free(filename);
    free(buffer);
    free(f2);
    free(symlink);
    free(path);
}