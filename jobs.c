#include "headers.h"
#include "jobs.h"

void sort_job_names(job *jobs)
{
    int n = *bgp_count;
    qsort(jobs, n, sizeof(job), compare_job_names);
}

void print_jobs_info(job *jobs, int *bgp_count, char **tokens)
{

    int n = *bgp_count;
    int nts = no_of_strings(tokens);

    qsort(jobs, n, sizeof(job), compare_job_names);

    for (int i = 0; i < n; i++)
    {

        char *filename = malloc(200);
        sprintf(filename, "/proc/%d/stat", jobs[i].pid);
        // printf("%s\n", filename);
        FILE *f = fopen(filename, "r");

        int unused;
        char *buffer = malloc(1000);

        fgets(buffer, 1000, f);

        //this gives name in parentheses
        char *name = malloc(100);
        char **info = tokenize(buffer, " ");
        name = info[1];
        char *state = info[2];

        if (nts == 1)
        {
            if (strcmp(state, "S") == 0)
            {

                printf("[%d] ", jobs[i].job_no);

                printf("Stopped ");
                printf("%s ", jobs[i].name);
                printf("[%d]\n", jobs[i].pid);
            }
            else if (strcmp(state, "R") == 0)
            {
                printf("[%d] ", jobs[i].job_no);

                printf("Running ");
                printf("%s ", jobs[i].name);
                printf("[%d]\n", jobs[i].pid);
            }
            else if (strcmp(state, "T") == 0)
            {
                printf("[%d] ", jobs[i].job_no);

                printf("Stopped ");
                printf("%s ", jobs[i].name);
                printf("[%d]\n", jobs[i].pid);
            }
        }
        else if (nts >= 2)
        {
            if (strcmp(tokens[1], "-r"))
            {
                if (strcmp(state, "R") == 0)
                {
                    printf("[%d] ", jobs[i].job_no);

                    printf("Running ");
                    printf("%s ", jobs[i].name);
                    printf("[%d]\n", jobs[i].pid);
                }
            }
            else if (strcmp(tokens[1], "-s"))
            {
                if (strcmp(state, "T") == 0)
                {
                    printf("[%d] ", jobs[i].job_no);

                    printf("Stopped ");
                    printf("%s ", jobs[i].name);
                    printf("[%d]\n", jobs[i].pid);
                }
            }
        }

        else
        {
            printf("command not supported\n");
        }

        fclose(f);
        free(filename);
        free(buffer);
    }
}
