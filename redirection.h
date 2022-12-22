#ifndef __REDIR_
#define __REDIR_

int *has_redirection(char **tokens);
int *input_redirection_present(char **tokens);
int implement_input_redirection(int index, char **tokens);

int *output_redirection_present(char **tokens);
int implement_output_redirection(int index, char **tokens);

int check_and_do_redirection(char **tokens);
void restore_fds();
#endif