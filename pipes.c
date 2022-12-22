#include "headers.h"
#include "functions.h"
#include "executing_commands.h"
#include "redirection.h"

int no_of_pipes_present(char **tokens)
{

    int n1 = no_of_strings(tokens);
    int count = 0;
    for (int i = 0; i < n1; i++)
    {

        if (strcmp(tokens[i], "|") == 0)
        {

            count++;
        }
    }
    return count;
}

//function for commands sepeerated by pipes
//you have the command tokened by ; or whatever
//before tokenizing by " \t" tokenize by "|"
//and then tokenize by " \t"

int spawn_proc(int in, int out, char **tokens)
{
    pid_t pid;
    int wstatus;
    pid = fork();
    if (pid == 0)
    {

        //child process
        signal(SIGINT, SIG_DFL);
        signal(SIGTSTP, SIG_DFL);
        if (in != 0)
        {
            dup2(in, 0);
            printf("ok-1\n");
            close(in);
        }

        if (out != 1)
        {
            dup2(out, 1);
            printf("ok-2\n");

            close(out);
        }

        // return execvp(cmd->argv[0], (char *const *)cmd->argv);

        //
        // execute_all(tokens);
        if (is_builtin(tokens[0]))
        {
            // execute_builtin(tokens);
            int *xr = has_redirection(tokens);
            if (xr[0] > 0)
            {
                //has redirection
                printf("before redirection in builtin \n");

                int err = check_and_do_redirection(tokens);
                execute_builtin(tokens);
                printf("redirection in builtin is present\n");
                // restore_fds();
                printf("called after restoring fds-------redirection in builtin is present\n");
            }

            else
            {
                printf("1---redirection in builtin is not present\n");

                execute_builtin(tokens);
                printf("2---redirection in builtin is not present\n");
            }
        }

        else
        {
            //not builtin
            int *xr = has_redirection(tokens);
            if (xr[0] > 0)
            {
                printf("redirection in not-builtin is present\n");
                printf("1--exit");

                printf("Child PID is %ld\n", (long)getpid());

                int rederr = check_and_do_redirection(tokens);
                int ss = 0;
                ss = execvp(tokens[0], tokens);
                if (ss == -1)
                {
                    if (errno == EACCES)
                    {
                        printf("Search permission is denied on a component of the path or Execute permission is denied for the file\n or a script or ELF interpreter or The filesystem is mounted");
                    }
                    perror("");
                }
                // restore_fds();
            }
            else
            {
                //doesnot have reidretion
                int ss = 0;
                printf("fffffffffff\n");
                ss = execvp(tokens[0], tokens);
                if (ss == -1)
                {
                    if (errno == EACCES)
                    {
                        printf("Search permission is denied on a component of the path or Execute permission is denied for the file\n or a script or ELF interpreter or The filesystem is mounted");
                    }
                    perror("");
                }
            }
        }
    }
    else if (pid < 0)
    {
        perror("forking error");
    }

    else
    {
        //parent process
        printf("ok-3\n");

        // restore_fds();
        printf("ok-4\n");

        // do
        // {

        // int w = waitpid(pid, &wstatus, WUNTRACED | WCONTINUED);
        //     if (w == -1)
        //     {
        //         perror("waitpid");
        //         exit(EXIT_FAILURE);
        //     }

        //     if (WIFEXITED(wstatus))
        //     {
        //         // printf("exited, status=%d\n", WEXITSTATUS(wstatus));
        //         // printf("%s with pid %d exited with exit status=%d\n", tokens[0], cpid, WEXITSTATUS(wstatus));
        //     }
        //     else if (WIFSIGNALED(wstatus))
        //     {
        //         printf("killed by signal %d\n", WTERMSIG(wstatus));
        //     }
        //     else if (WIFSTOPPED(wstatus))
        //     {
        //         printf("stopped by signal %d\n", WSTOPSIG(wstatus));
        //     }
        //     else if (WIFCONTINUED(wstatus))
        //     {
        //         printf("continued\n");
        //     }
        // } while (!WIFEXITED(wstatus) && !WIFSIGNALED(wstatus));
    }

    return pid;
}

//commands_p-->command contains pipe
int fork_pipes(int n, char **commands_p)
{
    int i;
    pid_t pid;
    int wstatus;

    int in, fd[2];

    /* The first process should get its input from the original file descriptor 0.  */
    in = STDIN_FILENO;

    /* Note the loop bound, we spawn here all, but the last stage of the pipeline.  */
    for (i = 0; i < n - 1; ++i)
    {

        pipe(fd);

        /* f [1] is the write end of the pipe, we carry `in` from the prev iteration.  */

        char **command_p_tokens = malloc(200); /////////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////         FREE IT ////////////////////////

        command_p_tokens = tokenize(commands_p[i], " \t");
        //////////////////////////////////////////////////////////////////////////////////////////
        print_tokens(command_p_tokens); ///////////////  DELETE THIS
        ////////////////////////////////////////////////////////////////////////////////
        spawn_proc(in, fd[1], command_p_tokens);

        /* No need for the write end of the pipe, the child will write here.  */
        close(fd[1]);
        // close(fd[0]);

        /* Keep the read end of the pipe, the next child will read from there.  */
        in = fd[0];
        close(fd[0]);
    }

    /* Last stage of the pipeline - set stdin be the read end of the previous pipe
     and output to the original file descriptor 1. */
    if (in != 0)
        dup2(in, 0);

    /* Execute the last stage with the current process. */
    // return execvp(cmd[i].argv[0], (char *const *)cmd[i].argv);
    char **last_command = malloc(100);
    last_command = tokenize(commands_p[i], " \t");
    pid = fork();
    if (pid == 0)
    {

        //child process
        signal(SIGINT, SIG_DFL);
        signal(SIGTSTP, SIG_DFL);

        // execute_all(last_command);
        if (is_builtin(last_command[0]))
        {
            // execute_builtin(tokens);
            int *xr = has_redirection(last_command);
            if (xr[0] > 0)
            {

                printf("before redirection in builtin \n");

                int err = check_and_do_redirection(last_command);
                execute_builtin(last_command);
                printf("redirection in builtin is present\n");
                // restore_fds();
                printf("called after restoring fds-------redirection in builtin is present\n");
            }

            else
            {
                printf("1---redirection in builtin is not present\n");

                execute_builtin(last_command);
                printf("2---redirection in builtin is not present\n");
            }
        }

        else
        {
            int *xr = has_redirection(last_command);
            if (xr[0] > 0)
            {
                printf("redirection in not-builtin is present\n");
                printf("1--exit");

                printf("Child PID is %ld\n", (long)getpid());

                int rederr = check_and_do_redirection(last_command);
                int ss = 0;
                ss = execvp(last_command[0], last_command);
                if (ss == -1)
                {
                    if (errno == EACCES)
                    {
                        printf("Search permission is denied on a component of the path or Execute permission is denied for the file\n or a script or ELF interpreter or The filesystem is mounted");
                    }
                    perror("");
                }
                // restore_fds();
            }
            else
            {
                //doesnot have reidretion
                int ss = 0;
                ss = execvp(last_command[0], last_command);
                if (ss == -1)
                {
                    if (errno == EACCES)
                    {
                        printf("Search permission is denied on a component of the path or Execute permission is denied for the file\n or a script or ELF interpreter or The filesystem is mounted");
                    }
                    perror("");
                }
            }
        }
    }

    else
    {
        //parent process
        printf("ok-5\n");

        // restore_fds();
        printf("ok-6\n");

        // do
        // {
        printf("parent waiting\n");
        // int w = waitpid(pid, &wstatus, NULL);
        // wait(NULL);
        //     if (w == -1)
        //     {
        //         perror("waitpid");
        //         exit(EXIT_FAILURE);
        //     }

        //     if (WIFEXITED(wstatus))
        //     {
        //         // printf("exited, status=%d\n", WEXITSTATUS(wstatus));
        //         // printf("%s with pid %d exited with exit status=%d\n", tokens[0], cpid, WEXITSTATUS(wstatus));
        //     }
        //     else if (WIFSIGNALED(wstatus))
        //     {
        //         printf("killed by signal %d\n", WTERMSIG(wstatus));
        //     }
        //     else if (WIFSTOPPED(wstatus))
        //     {
        //         printf("stopped by signal %d\n", WSTOPSIG(wstatus));
        //     }
        //     else if (WIFCONTINUED(wstatus))
        //     {
        //         printf("continued\n");
        //     }
        // } while (!WIFEXITED(wstatus) && !WIFSIGNALED(wstatus));
        restore_fds();
    }
    printf("waiting over\n");

    free(last_command);

    // restore_fds();
}
