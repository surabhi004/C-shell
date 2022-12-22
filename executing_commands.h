#ifndef __EXECUTING_C
#define __EXECUTING_C

//describe functionality----------------------------------
void execute_foreground(char **tokens);

void execute_background(char **tokens);

int is_builtin(char *command);

int execute_builtin(char **tokens);

void execute_all(char **tokens);
void sigstp_handler_child(int signo);

#endif
