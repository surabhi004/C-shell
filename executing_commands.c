#include "headers.h"

#include "cd.h"
#include "ls.h"
#include "other_builtins.h"
#include "pinfo.h"
#include "repeat.h"
#include "redirection.h"
#include "pipes.h"
#include "jobs.h"
#include <signal.h>

typedef void (*sighandler_t)(int);

sighandler_t sigstp_handler_child(int signo, int pid)
{

    kill(getpid(), SIGTTIN);

    tcsetpgrp(0, pid);
}

void execute_foreground(char **tokens)
{
    pid_t cpid, w;
    int wstatus;

    cpid = fork();
    if (cpid == -1)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (cpid == 0)
    {
        //child process
        signal(SIGINT, SIG_DFL);
        signal(SIGTSTP, SIG_DFL);

        // printf("Child PID is %ld\n", (long)getpid());

        //CHECK AND DO REDIRECTION
        int *red = has_redirection(tokens);

        if (red[0] > 0)
        {
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
            restore_fds();
        }
        else
        {
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
        }
    }

    else if (cpid < 0)
    {
        perror("forking error");
    }

    else
    {
        //parent process

        do
        {
            w = waitpid(cpid, &wstatus, WUNTRACED | WCONTINUED);
            if (w == -1)
            {
                perror("waitpid");
                exit(EXIT_FAILURE);
            }

            if (WIFEXITED(wstatus))
            {
                // printf("exited, status=%d\n", WEXITSTATUS(wstatus));
                // printf("%s with pid %d exited with exit status=%d\n", tokens[0], cpid, WEXITSTATUS(wstatus));
            }
            else if (WIFSIGNALED(wstatus))
            {
                printf("killed by signal %d\n", WTERMSIG(wstatus));
            }
            else if (WIFSTOPPED(wstatus))
            {
                printf("stopped by signal %d\n", WSTOPSIG(wstatus));
            }
            else if (WIFCONTINUED(wstatus))
            {
                printf("continued\n");
            }
        } while (!WIFEXITED(wstatus) && !WIFSIGNALED(wstatus));
    }
}

void execute_background(char **tokens)
{
    pid_t cpid;
    int *w;
    int wstatus;

    cpid = fork();
    if (cpid == -1)
    {
        perror("fork");
    }

    if (cpid == 0)
    {
        //child process
        signal(SIGINT, SIG_DFL);
        signal(SIGTSTP, SIG_DFL);

        //CHECK AND DO REDIRECTION
        setpgid(0, 0);

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
    }

    else
    {
        //parent process
        // printf("[%d] %d\n", *bgp_count, cpid);
        bgp_pids[*bgp_count] = cpid;
        jobs[*bgp_count].pid = cpid;
        jobs[*bgp_count].name = tokens[0];
        jobs[*bgp_count].job_no = *bgp_count;
        print_bpg_pids(bgp_pids);

        (*bgp_count)++;
        // printf("%d\n", *bgp_count);
    }
}

int is_builtin(char *command)
{

    if (strcmp(command, "ls") == 0)
    {
        return 1;
    }
    else if (strcmp(command, "cd") == 0)
    {
        return 1;
    }
    else if (strcmp(command, "pwd") == 0)
    {
        return 1;
    }
    else if (strcmp(command, "echo") == 0)
    {
        return 1;
    }
    else if (strcmp(command, "pinfo") == 0)
    {
        return 1;
    }
    else if (strcmp(command, "repeat") == 0)
    {
        return 1;
    }
    else if (strcmp(command, "jobs") == 0)
    {
        return 1;
    }
    else if (strcmp(command, "fg") == 0)
    {
        return 1;
    }
    else if (strcmp(command, "bg") == 0)
    {
        return 1;
    }
    else if (strcmp(command, "sig") == 0)
    {
        return 1;
    }
    else if (strcmp(command, "replay") == 0)
    {
        return 1;
    }

    else
    {
        return 0;
    }
}

int execute_builtin(char **tokens)
{
    if (strcmp(tokens[0], "cd") == 0)
    {

        int cd_ret = change_dir(tokens[1], last_cd_input);
    }

    else if (strcmp(tokens[0], "ls") == 0)
    {
        int su = ls_execute(tokens);
    }
    else if (strcmp(tokens[0], "pwd") == 0)
    {
        int su = pwd_x();
    }
    else if (strcmp(tokens[0], "echo") == 0)
    {
        echo_x(tokens);
    }
    else if (strcmp(tokens[0], "pinfo") == 0)
    {
        pinfo_x(tokens);
    }
    else if (strcmp(tokens[0], "repeat") == 0)
    {
        repeat_x(tokens);
    }
    else if (strcmp(tokens[0], "jobs") == 0)
    {
        print_jobs_info(jobs, bgp_count, tokens);
    }

    else if (strcmp(tokens[0], "fg") == 0)
    {
        fg(tokens, jobs, bgp_count);
    }
    else if (strcmp(tokens[0], "bg") == 0)
    {
        bg(tokens, jobs, bgp_count);
    }
    else if (strcmp(tokens[0], "sig") == 0)
    {
        sig(tokens, jobs, bgp_count);
    }
    else if (strcmp(tokens[0], "replay") == 0)
    {
        replay(tokens);
    }
    else
    {
        printf("Command Not Found.\n");
    }
}

void execute_all(char **tokens)
{

    int nt = no_of_strings(tokens);
    if (nt > 1)
    {
        if (strcmp(tokens[1], "&") == 0)
        {
            execute_background(tokens);
        }
        else
        {
            //foreground

            if (is_builtin(tokens[0]))
            {
                // execute_builtin(tokens);
                int *xr = has_redirection(tokens);
                if (xr[0] > 0)
                {
                    // printf("before redirection in builtin \n");

                    int err = check_and_do_redirection(tokens);
                    execute_builtin(tokens);
                    // printf("redirection in builtin is present\n");
                    restore_fds();
                    // printf("called after restoring fds-------redirection in builtin is present\n");
                }

                else
                {
                    // printf("1---redirection in builtin is not present\n");

                    execute_builtin(tokens);
                    // printf("2---redirection in builtin is not present\n");
                }
            }
            else
            {
                int *xr = has_redirection(tokens);
                if (xr[0] > 0)
                {
                    // printf("redirection in not-builtin is present\n");
                    // printf("1--exit");
                    execute_foreground(tokens);
                    // printf("before restoring fds\n");
                    restore_fds();
                    // printf("after restoring fds\n");
                }

                else
                {
                    // printf("1---redirection in not-builtin is not present\n");

                    execute_foreground(tokens);
                    // printf("2---redirection in not-builtin is not present\n");
                }
            }
        }
    }
    else
    {
        if (is_builtin(tokens[0]))
        {
            execute_builtin(tokens);
        }
        else
        {
            execute_foreground(tokens);
        }
    }
}
