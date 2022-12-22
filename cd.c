#include "headers.h"
#include "functions.h"

//checks if the working directory has the home directory(directory where the shell executable resides)
char *check(char *curr_path, char *home_dir)
{

    int ans = 0;
    char *relative_path = malloc(350 * sizeof(char));

    char **abs_path_tokens = tokenize(curr_path, "/");
    int home_dir_position = 0;
    int len = no_of_strings(abs_path_tokens);
    for (int i = 0; i < len; i++)
    {
        if (strcmp(abs_path_tokens[i], home_dir) == 0)
        {
            home_dir_position = i;
            ans = 1;
            break;
        }
    }
    if (ans == 1)
    {

        strcat(relative_path, "~");
        for (int i = home_dir_position + 1; i < len; i++)
        {
            strcat(relative_path, "/");
            strcat(relative_path, abs_path_tokens[i]);
        }
        return relative_path;
    }
    free(abs_path_tokens);
    free(relative_path);
    return NULL;
}

char *find_final_path(char *dir_or_path, char *home_dir)
{

    char *r = check(get_cwd_path(), home_dir);
    char *x = malloc(500 * sizeof(char));

    if (r != NULL)
    {
        x = r;
    }
    else
    {
        //just get path normally
        x = get_cwd_path();
    }
    return x;
    free(r);
    free(x);
}

int change_dir(char *dir_or_path, char *last_cd_input)
{

    if (strcmp(dir_or_path, "-") == 0)
    {
        int n = chdir(last_cd_input);
        if (n != 0)
        {
            printf("Could not change directory to %s\n", dir_or_path);
            if (errno == EACCES)
            {
                printf("%s\n", "Search permission is denied for one of the components of path.");
            }
            else if (errno == EFAULT)
            {
                printf("%s\n", "path points outside your accessible address space.");
            }
            else if (errno == EIO)
            {
                printf("%s\n", "An I/O error occurred.");
            }
            else if (errno == ENAMETOOLONG)
            {
                printf("%s\n", "path is too long.");
            }
            else if (errno == ENOENT)
            {
                printf("%s\n", "The directory specified in path does not exist.");
            }
            else if (errno == ENOTDIR)
            {
                printf("%s\n", "A component of path is not a directory.");
            }
            else if (errno == ENOMEM)
            {
                printf("%s\n", "Insufficient kernel memory was available.");
            }

            perror("");
            return 1;
        }

        return 0;
    }

    int n = chdir(dir_or_path);
    if (n != 0)
    {
        printf("Could not change directory to %s\n", dir_or_path);
        if (errno == EACCES)
        {
            printf("%s\n", "Search permission is denied for one of the components of path.");
        }
        else if (errno == EFAULT)
        {
            printf("%s\n", "path points outside your accessible address space.");
        }
        else if (errno == EIO)
        {
            printf("%s\n", "An I/O error occurred.");
        }
        else if (errno == ENAMETOOLONG)
        {
            printf("%s\n", "path is too long.");
        }
        else if (errno == ENOENT)
        {
            printf("%s\n", "The directory specified in path does not exist.");
        }
        else if (errno == ENOTDIR)
        {
            printf("%s\n", "A component of path is not a directory.");
        }
        else if (errno == ENOMEM)
        {
            printf("%s\n", "Insufficient kernel memory was available.");
        }

        perror("");
        return 1;
    }

    //save last cd command
    // char *temp_c = get_cwd_path();
    // strcpy(last_cd_input, temp_c);

    return 0;
}
