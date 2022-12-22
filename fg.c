#include "headers.h"
#include "jobs.h"
#include "executing_commands.h"

void fg(char **tokens, job *jobs, int *bgp_count)
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
            printf("No such job/n");
        else
        {
            pid_t pid = jobs[process_no].pid;
            char stat[1000];
            char status;
            int p;
            long unsigned mem;
            char filename[20];
            // sprintf(str, "%d", jobs[process_no].pid);

            // strcpy(stat, "/proc/");
            // strcat(stat, str);
            // strcat(stat, "/stat");

            sprintf(filename, "/proc/%d/stat", pid);

            FILE *fd;
            if ((fd = fopen(filename, "r")) == NULL)
            {
                printf("Process has been terminated. Cannot bring to foreground.\n");
                perror("COULDNOT OPEN FILE");
            }
            else
            {
                int ppid;
                int pgrp;
                int tpgid;
                fscanf(fd, "%*d %*s %*c %d %d %*d %*d %d", &ppid, &pgrp, &tpgid);
                // printf("ppid of the bg is %d\n", (int)ppid);
                // printf("The ID of the foreground process group of the controlling terminal of the process------>> %d\n", (int)tpgid);

                // printf("pgrp of the bg is %d\n", (int)pgrp);

                pid_t xpid;

                if ((xpid = tcgetpgrp(STDOUT_FILENO)) < 0)
                    perror("tcgetpgrp() error");
                // else
                //     printf("the foreground process group id of stdout is %d\n",
                //            (int)xpid);
                // printf("pid of the bg process is %d\n", pid);

                // setpgid(pid, xpid);
                kill(pid, SIGCONT);
                // tcsetpgrp(0, pid);

                //find & ,remkve & and execute it in foreground
                //fork and execvp
                char *a[] = {jobs[process_no].name, NULL};
                int x = fork();
                int wstatus;

                if (x == 0)
                {
                    execvp(jobs[process_no].name, a);
                }
                else if (x == -1)
                {
                    perror("");
                }
                else
                {
                    waitpid(pid, &wstatus, WUNTRACED);
                }

                //and set the gpid of the child id to the pgid

                //i think i need to make something like forejobs and backjobs
                // strcpy(fore.name, back[proc].name);
                // fore.pid = back[proc].pid;
                // fore.is_back = 0;
                int j = process_no;
                for (j = process_no; j < *bgp_count; j++)
                {
                    jobs[j] = jobs[j + 1];
                }
                (*bgp_count)--;
                waitpid(-1, NULL, WUNTRACED);
            }
        }
    }
}