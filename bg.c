#include "headers.h"
#include "jobs.h"

void bg(char **tokens, job *jobs, int *bgp_count)
{
    int process_no = atoi(tokens[1]);
    int args = no_of_strings(tokens);

    if (args >= 3)
        printf("Too many arguments\n");
    else if (args == 1)
        printf("Too few arguments\n");
    else
    {
        if (process_no > *bgp_count)
            printf("No such job\n");
        else
        {
            pid_t pid = jobs[process_no].pid;
            kill(pid, SIGTTIN);
            kill(pid, SIGCONT);
        }
    }
}