#include "headers.h"
#include <sys/types.h>
#include <pwd.h>
#include <grp.h>
#include <dirent.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>

long int total_block_size(char *dir)
{

    long int size = 0;

    DIR *dir1 = opendir(dir);
    if (dir == NULL)
    {
        perror("Cant open directory");
    }

    struct dirent *dir_or_file;
    dir_or_file = readdir(dir1);

    while (dir_or_file != NULL)
    {
        struct stat statbuf_f;
        int success = lstat(dir_or_file->d_name, &statbuf_f);
        if (success == -1)
        {
            if (errno == EACCES)
            {
                perror("Search permission is denied for one of the directories in the path prefix of  pathname.");
            }
            else if (errno == EBADF)
            {
                perror("fd is not a valid open file descriptor.");
            }
            else if (errno == ELOOP)
            {
                perror("Too many symbolic links encountered while traversing the path.");
            }
            else if (errno == ENAMETOOLONG)
            {
                perror("pathname is too long.");
            }
            else if (errno == ENOMEM)
            {
                perror("Out of memory");
            }
            else if (errno == ENOTDIR)
            {
                perror("A component of the path prefix of pathname is not a directory.");
            }
        }
        size += statbuf_f.st_blocks;
        //if a option given then
        dir_or_file = readdir(dir1);
    }

    closedir(dir1);

    return size;
}

void print_file_details(char *name)
{

    struct stat statbuf;
    int success = lstat(name, &statbuf);
    if (success == -1)
    {
        if (errno == EACCES)
        {
            perror("Search permission is denied for one of the directories in the path prefix of  pathname.");
        }
        else if (errno == EBADF)
        {
            perror("fd is not a valid open file descriptor.");
        }
        else if (errno == ELOOP)
        {
            perror("Too many symbolic links encountered while traversing the path.");
        }
        else if (errno == ENAMETOOLONG)
        {
            perror("pathname is too long.");
        }
        else if (errno == ENOMEM)
        {
            perror("Out of memory");
        }
        else if (errno == ENOTDIR)
        {
            perror("A component of the path prefix of pathname is not a directory.");
        }
    }

    printf((S_ISDIR(statbuf.st_mode)) ? "d" : "-");
    //permissions

    printf((statbuf.st_mode & S_IRUSR) ? "r" : "-");
    printf((statbuf.st_mode & S_IWUSR) ? "w" : "-");
    printf((statbuf.st_mode & S_IXUSR) ? "x" : "-");
    printf((statbuf.st_mode & S_IRGRP) ? "r" : "-");
    printf((statbuf.st_mode & S_IWGRP) ? "w" : "-");
    printf((statbuf.st_mode & S_IXGRP) ? "x" : "-");
    printf((statbuf.st_mode & S_IROTH) ? "r" : "-");
    printf((statbuf.st_mode & S_IWOTH) ? "w" : "-");
    printf((statbuf.st_mode & S_IXOTH) ? "x" : "-");

    printf(" ");
    //get how many links
    printf("%ld", statbuf.st_nlink);
    printf(" ");

    //owner and group owner of directory or file
    struct passwd *own = getpwuid(statbuf.st_uid);
    struct group *grp = getgrgid(statbuf.st_gid);
    if (own != 0)
    {
        printf("%s", own->pw_name);
    }
    printf(" ");
    if (grp != 0)
    {
        printf("%s", grp->gr_name);
    }
    printf(" ");

    //size of file or directory in bytes

    printf("%ld", statbuf.st_size);
    printf(" ");

    //Time of last modification
    char time[100];
    strftime(time, 100, "%b %d %Y %H:%S", localtime(&statbuf.st_mtime));

    printf("%s", time);
    printf(" ");

    printf("%s", name);
    printf("\n");
}

char **ls_x(char **option_tokens)
{
    int all = 0;
    int long_form = 0;
    char **ans = malloc(250 * sizeof(char));
    int no_of_tokens = no_of_strings(option_tokens);

    char *fname = malloc(250 * sizeof(char));
    if (no_of_tokens == 1)
    {
        //only ls given
        //print current directory

        fname = ".";
        ans[2] = fname;
        ans[0] = "0"; //not all
        ans[1] = "0"; //not long form
        return ans;
    }

    int j = 2;
    ans[0] = "0";
    ans[1] = "0";

    for (int i = 1; i < no_of_tokens; i++)
    {
        if (option_tokens[i][0] == '-')
        {
            char *tstr = option_tokens[1];

            int s_n = strlen(option_tokens[i]);
            for (int k = 1; k < s_n; k++)
            {
                if (option_tokens[i][k] == 'a')
                {
                    all = 1;
                    ans[0] = malloc(10);
                    char *x = strcpy(ans[0], "1");
                }
                if (option_tokens[i][k] == 'l')
                {
                    long_form = 1;
                    ans[1] = malloc(10);
                    char *x = strcpy(ans[1], "1");
                }
            }
        }
        else
        {
            ans[j] = malloc(50);
            ans[j] = option_tokens[i];

            j++;
        }
    }

    return ans;
}

void print_ls(char **info)
{

    int no_info = no_of_strings(info);

    if (info[2] == NULL)
    {
        info[2] = malloc(20 * sizeof(char));
        strcpy(info[2], ".");

        DIR *dir = opendir(info[2]);
        if (dir == NULL)
        {
            perror("Cant open directory");
        }

        struct dirent *dir_or_file;
        dir_or_file = readdir(dir);
        printf("total %ld\n", total_block_size(info[2]));

        while (dir_or_file != NULL)
        {
            struct stat statbuf_f;
            lstat(dir_or_file->d_name, &statbuf_f);
            char *name = dir_or_file->d_name;

            //if a option given then

            if (name[0] == '.')

            {

                if (strcmp(info[0], "1") == 0)
                {
                    if (strcmp(info[1], "1") == 0)
                    {

                        print_file_details(name);
                    }
                    else
                    {
                        printf("%s ", name);
                    }
                }
            }
            else
            {
                if (strcmp(info[1], "1") == 0)
                {

                    print_file_details(name);
                }
                else
                {
                    printf("%s  ", name);
                }
            }
            dir_or_file = readdir(dir);
        }
        printf("\n\n");

        closedir(dir);
        return;
    }

    no_info = no_of_strings(info);

    for (int k = 2; k < no_info; k++)
    {

        if (no_info > 3)
        {
            printf("%s\n", info[k]);
        }

        struct stat statbuf;
        lstat(info[k], &statbuf);
        //checks if it is a file or directory
        if (!S_ISDIR(statbuf.st_mode))
        {
            if (strcmp(info[1], "0") == 0)
            {
                printf("%s\n", info[k]);
            }

            else if (strcmp(info[1], "1") == 0)
            {
                print_file_details(info[k]);
            }
        }
        else if (S_ISDIR(statbuf.st_mode))
        {
            DIR *dir = opendir(info[k]);
            if (dir == NULL)
            {
                perror("Cant open directory");
            }

            else
            {
                struct dirent *dir_or_file;
                dir_or_file = readdir(dir);
                printf("total %ld\n", total_block_size(dir_or_file->d_name));

                while (dir_or_file != NULL)
                {
                    struct stat statbuf_f;
                    lstat(dir_or_file->d_name, &statbuf_f);
                    char *name = dir_or_file->d_name;
                    //if a option given then

                    if (name[0] == '.')
                    {

                        if (strcmp(info[0], "1") == 0)
                        {
                            if (strcmp(info[1], "1") == 0)
                            {
                                print_file_details(name);
                            }
                            else
                            {
                                printf("%s  ", name);
                            }
                        }
                    }
                    else
                    {

                        if (strcmp(info[1], "1") == 0)
                        {
                            print_file_details(name);
                        }
                        else
                        {
                            printf("%s  ", name);
                        }
                    }
                    dir_or_file = readdir(dir);
                }
                printf("\n\n");

                closedir(dir);
            }
        }
    }
}

int ls_execute(char **tokens)
{

    char **orig = tokens;
    char **option_tokens = ls_x(tokens);
    print_ls(option_tokens);
    return 0;
}
