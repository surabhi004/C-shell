#include "headers.h"
#include <signal.h>

// void sigtstp_handler(int signum)
// {
//     printf("\033[1;31mEt tu brute?\n\033[0m");
//     return;
// }
// void sigint_handler(int signum)
// {
//     printf("\033[1;31mThe curtains fall.\n\033[0m");
//     exit(0);
// }

// void signals()
// {
//     signal(SIGINT, sigint_handler);
//     signal(SIGTSTP, sigtstp_handler);
// }

// int main()
// {
//     signal(SIGINT, sigint_handler);
//     signal(SIGTSTP, sigtstp_handler);
//     // signal system call binds a signal with a user-defined signal handler function.

//     while (1)
//     {
//         ;
//     }
//     return 0;
// }
