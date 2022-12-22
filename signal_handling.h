#ifndef __SIGNAL_H
#define __SIGNAL_H

void sigtstp_handler(int signum);

void sigint_handler(int signum);
void signals();

#endif