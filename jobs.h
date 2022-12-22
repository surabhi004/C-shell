// #ifndef __JOBS_
// #define __JOBS_

// typedef struct job
// {
//     // char name[100];
//     char *name;
//     int pid;
//     //int state;
//     int is_back;
//     int job_no;
// } job;

// const int max_jobs = 100;

// // job jobs[max_jobs];-->giving error-->jobs.h:16:5: error: variably modified ‘bgp_pids’ at file scope
// //    16 | int bgp_pids[max_jobs];

// int bgp_pids[100];

// int bgp_count = 0;

// job jobs[100];

// void sort_job_names(job jobs[]);
// void print_jobs_info(job jobs[]);

// #endif

// //if this doesnot declare everyhting in headers.h file

#ifndef __JOBS_
#define __JOBS_
typedef struct job
{
    // char name[100];
    char *name;
    int pid;
    //int state;
    int is_back;
    int job_no;
} job;

static const int max_jobs = 100;

// job jobs[max_jobs];-->giving error-->jobs.h:16:5: error: variably modified ‘bgp_pids’ at file scope
//    16 | int bgp_pids[max_jobs];

// static int bgp_pids[100];
static int bgp_pids[100];

// extern int bgp_count = 0;
static int var = 0;
static int *bgp_count = &var;

//background jobs
job jobs[100];

void sort_job_names(job *jobs);
void print_jobs_info(job *jobs, int *bgp_count, char **tokens);

void fg(char **tokens, job *jobs, int *bgp_count);
void bg(char **tokens, job *jobs, int *bgp_count);
void sig(char **tokens, job *jobs, int *bgp_count);
void replay(char **tokens);
#endif