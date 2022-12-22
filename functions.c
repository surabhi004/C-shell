#include "functions.h"
#include "headers.h"
#include "jobs.h"

char *getline_t()
{
    char *buffer;
    size_t bufsize = 100;
    size_t characters;

    buffer = (char *)malloc(bufsize * sizeof(char));
    if (buffer == NULL)
    {
        perror("Unable to allocate buffer");
        exit(1);
    }

    characters = getline(&buffer, &bufsize, stdin);

    return buffer;
}

//tokenizes the string

char **tokenize(char *s, char *delimiter)
{

    char *original = s;

    int size = 500;
    char **tokens = malloc(size * sizeof(char *));
    if (!tokens)
    {
        perror("Allocation error");
        // return 1;
        exit(0);
    }
    int i = 0;

    char *x = malloc(100 * sizeof(char));

    x = strtok(s, delimiter);

    while (x != NULL)
    {
        tokens[i] = x;
        x = strtok(NULL, delimiter);
        i++;
        if (i >= size)
        {
            size += 100;
            tokens = realloc(tokens, size * sizeof(char *));
            if (!tokens)
            {
                perror("Allocation error");
                // return 1;
                exit(0);
            }
        }
    }
    tokens[i] = NULL;
    return tokens;
}

int no_of_strings(char **x)
{
    //only on null terminated strings array-last elemnet of array should be null
    int no = 1;
    while (x[no++] != NULL)
    {
    }
    return no - 1;
}

//FOR DEBUGGING PURPOSES
void print_tokens(char **s)
{
    int len = no_of_strings(s);

    for (int j = 0; j < len; j++)
    {
        printf("%s\n", s[j]);
    }
}

char *get_dir(char *abs_path)
{
    char **tokens = tokenize(abs_path, "/");
    int n = no_of_strings(tokens);
    return tokens[n - 1];
}

//get curent working dir path

char *get_cwd_path()
{
    char *x = malloc(250 * sizeof(char));
    char *path = getcwd(x, 250);
    if (path == NULL)
    {
        if (errno == EACCES)
        {
            printf("Permission to read or search a component of the filename was denied.\n");
        }
        else if (errno == EFAULT)
        {
            printf("buf points to a bad address.\n");
        }
        else if (errno == EINVAL)
        {
            printf("The size argument is zero and buf is not a null pointer.\n");
        }
        else if (errno == ENAMETOOLONG)
        {
            printf("The size of the null-terminated absolute pathname string exceeds PATH_MAX bytes.\n");
        }
        else if (errno == ENOENT)
        {
            printf("The current working directory has been unlinked.\n");
        }
        else if (errno == ENOMEM)
        {
            printf("Out of memory.\n");
        }
        else if (errno == ERANGE)
        {
            printf("The size argument is less than the length of the absolute pathname of the working directory, including the terminating null byte.  You need to allocate a bigger array and try again.\n");
        }
        else
        {
            perror("");
        }
    }
    return path;
}

char *get_system_name()
{
    char *name = malloc(200 * sizeof(char));
    int x = gethostname(name, 200);
    if (x != 0)
    {
        if (errno == ENAMETOOLONG)
        {
            printf("host name is too long.Allocate more memory\n");
        }
        else
        {
            perror("");
        }
    }
    return name;
}

void print_bpg_pids(int *bgp_pids) //bgp_pids[]
{

    for (int i = 0; i < *bgp_count; i++)
    {
        printf("%d\n", bgp_pids[*bgp_count]);
    }
}

int compare_job_names(const void *j1_name, const void *j2_name)
{

    const job *j1 = j1_name;
    const job *j2 = j2_name;

    return j1->name - j2->name;
}