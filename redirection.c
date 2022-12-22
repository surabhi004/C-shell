#include "redirection.h"
#include "headers.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "executing_commands.h"

//if no redirection return -1 else return positve number (not 0)
int *has_redirection(char **tokens)
{

    static int a[2];
    int nos = no_of_strings(tokens);
    for (int i = 0; i < nos; i++)
    {
        int ans = 0;

        if (strcmp(tokens[i], "<") == 0)
        {
            //has input redirection
            a[0] = 1;
            a[1] = i;
            return a;
        }

        else if (strcmp(tokens[i], ">") == 0)
        {
            //has ouput redirectionn
            a[0] = 2;
            a[1] = i;
            return a;
        }

        else if (strcmp(tokens[i], ">>") == 0)
        {
            //APPEND MODE
            a[0] = 3;
            a[1] = i;
            return a;
        }
    }
    a[0] = -1;
    return a;
}

//int index is the index_of_file_in_command
int *input_redirection_present(char **tokens)
{
    int nos = no_of_strings(tokens);
    static int a[2];

    for (int i = 0; i < nos; i++)
    {

        if (strcmp(tokens[i], "<") == 0)
        {
            //has input redirection
            a[0] = 1;
            a[1] = i;
        }
    }
    return a;
}

int implement_input_redirection(int index, char **tokens)
{
    char *input_file = (char *)malloc(100);
    strcpy(input_file, tokens[index]);

    int fd = open(input_file, O_RDONLY, 0644);

    if (fd < 0)
    {
        perror("Failed to open the given input file.");
        exit(1);
    }
    // printf("2-hi\n");

    // printf("You should see this on your screen.\n");

    originalINFD = dup(STDIN_FILENO);

    if (dup2(fd, STDIN_FILENO) < 0)
    {
        perror("Unable to duplicate file descriptor.");
        // exit(1);
    }
    // printf("3-hi\n");

    close(fd);
    //REMOVE THE < AND FILE

    tokens[index] = NULL;

    tokens[index - 1] = NULL;
    // print_tokens(tokens);

    // dup2(originalOUTFD, STDOUT_FILENO);
    // printf("7-hi\n");

    // printf("You should see this on your screen.\n");

    free(input_file);

    return 1;
}

int *output_redirection_present(char **tokens)
{
    int nos = no_of_strings(tokens);
    static int b[2];

    for (int i = 0; i < nos; i++)
    {

        if (strcmp(tokens[i], ">") == 0)
        {
            //has input redirection
            b[0] = 1;
            b[1] = i;
        }
    }
    return b;
}

int implement_output_redirection(int index, char **tokens)
{
    char *output_file = (char *)malloc(100);
    strcpy(output_file, tokens[index]);

    int fd = open(output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);

    if (fd < 0)
    {
        perror("Failed to open file.");
        // exit(1);
    }

    // printf("You should see this on your screen.\n");
    // static int originalOUTFD = 0;
    // dup2(STDOUT_FILENO, originalOUTFD);
    originalOUTFD = dup(STDOUT_FILENO);

    // duplicate the open file into stdout, closing stdout atomically
    if (dup2(fd, STDOUT_FILENO) < 0)
    {
        perror("Unable to duplicate file descriptor.");
        // exit(1);
    }

    // whether or not the original fd is closed, the duplicated fd remains accessible
    close(fd);

    //REMOVE THE < AND FILE

    tokens[index] = NULL;
    tokens[index - 1] = NULL;

    // dup2(originalOUTFD, STDOUT_FILENO);

    free(output_file);

    return 2;
}

int *output_append_redirection_present(char **tokens)
{
    int nos = no_of_strings(tokens);
    static int c[2];

    for (int i = 0; i < nos; i++)
    {

        if (strcmp(tokens[i], ">>") == 0)
        {
            //has input redirection
            c[0] = 1;
            c[1] = i;
        }
    }
    return c;
}

int implement_output_append_redirection(int index, char **tokens)
{
    char *output_file = (char *)malloc(100);
    strcpy(output_file, tokens[index]);

    int fd = open(output_file, O_WRONLY | O_CREAT | O_APPEND, 0644);

    if (fd < 0)
    {
        perror("Failed to open file.");
        // exit(1);
    }

    // printf("You should see this on your screen.\n");
    originalOUTFD = dup(STDOUT_FILENO);

    if (dup2(fd, STDOUT_FILENO) < 0)
    {
        perror("Unable to duplicate file descriptor.");
        // exit(1);
    }

    close(fd);

    //REMOVE THE < AND FILE

    tokens[index] = NULL;
    tokens[index - 1] = NULL;

    free(output_file);

    return 3;
}

int check_and_do_redirection(char **tokens)
{

    // int nos = no_of_strings(tokens);

    int *ret = has_redirection(tokens);

    int *i = input_redirection_present(tokens);
    int *o = output_redirection_present(tokens);
    int *oa = output_append_redirection_present(tokens);

    // int oa=output_append_redirection_present();
    if (i[0] == 1)
    {

        implement_input_redirection(i[1] + 1, tokens);
    }
    // fflush(1);

    if (o[0] == 1)
    {

        implement_output_redirection(o[1] + 1, tokens);
    }
    // if (oa[0] == 1)
    // {

    //     implement_output_redirection(o[1] + 1, tokens);
    // }
    if (oa[0] == 1)
    {

        implement_output_append_redirection(oa[1] + 1, tokens);
    }

    /*

    else if (ret[0] == 3)
    {
        //output redirection-apppend

        char *output_file = (char *)malloc(100);
        strcpy(output_file, tokens[ret[1] + 1]);

        int fd = open(output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);

        if (fd < 0)
        {
            perror("Failed to open file.");
            // exit(1);
        }

        printf("You should see this on your screen.\n");
        static int originalOUTFDA;
        dup2(STDOUT_FILENO, originalOUTFDA);

        // duplicate the open file into stdout, closing stdout atomically
        if (dup2(fd, STDOUT_FILENO) < 0)
        {
            perror("Unable to duplicate file descriptor.");
            // exit(1);
        }

        // whether or not the original fd is closed, the duplicated fd remains accessible
        close(fd);

        //execute the command
        // execute_all()
    //     int ss = 0;
    //     ss = execvp(tokens[0], tokens);
    //     if (ss == -1)
    //     {
    //         if (errno == EACCES)
    //         {
    //             printf("Search permission is denied on a component of the path or Execute permission is denied for the file\n or a script or ELF interpreter or The filesystem is mounted");
    //         }
    //         perror("");
    //     }
    //     free(output_file);
    //     return 3;
    // }
    */

    // free(ret);
    // free(i);
    // free(o);
    // free(oa);
}

void restore_fds()
{
    // printf("restroing fds");
    int x = dup2(originalOUTFD, STDOUT_FILENO);
    if (x < 0)
    {
        perror("");
        if (errno == EBADF)
        {
            perror("oldfd isn't an open file descriptor");
        }
        if (errno == EBUSY)
        {
            perror("(Linux only) This may be returned by dup2() or dup3() during a race condition with open(2) and dup()");
        }
        if (errno == EINTR)
        {
            perror("The dup2() or dup3() call was interrupted by a signal");
        }
        if (errno == EMFILE)
        {
            perror("The per-process limit on the number of open file descriptors has been reached ");
        }
    }
    int y = dup2(originalINFD, STDIN_FILENO);

    if (y < 0)
    {
        perror("");
        if (errno == EBADF)
        {
            perror("oldfd isn't an open file descriptor");
        }
        if (errno == EBUSY)
        {
            perror("(Linux only) This may be returned by dup2() or dup3() during a race condition with open(2) and dup()");
        }
        if (errno == EINTR)
        {
            perror("The dup2() or dup3() call was interrupted by a signal");
        }
        if (errno == EMFILE)
        {
            perror("The per-process limit on the number of open file descriptors has been reached ");
        }
    }

    // dup2(originalOUTFDA, STDOUT_FILENO);
}
