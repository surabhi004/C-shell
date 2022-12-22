#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#include <string.h>
#include <strings.h>
#include <errno.h>
#include <sys/wait.h>
#include "functions.h"
#include "prompt.h"
#include <signal.h>
#include <setjmp.h>

#include "cd.h"
#include "jobs.h"
static sigjmp_buf env;

char *last_cd_input;

int originalOUTFD;
int originalINFD;

// typedef struct job
// {
//     // char name[100];
//     char *name;
//     int pid;
//     //int state;
//     int is_back;
//     int job_no;
// } job;

// static const int max_jobs = 100;

// // job jobs[max_jobs];-->giving error-->jobs.h:16:5: error: variably modified ‘bgp_pids’ at file scope
// //    16 | int bgp_pids[max_jobs];

// // static int bgp_pids[100];
// extern int bgp_pids[100];

// extern int bgp_count = 0;

// job jobs[100];

// void sort_job_names(job *jobs);
// void print_jobs_info(job *jobs);
