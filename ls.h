#ifndef __LS_
#define __LS_

long int total_block_size(char *dir);
void print_file_details(char *name);
char **ls_x(char **option_tokens);
void print_ls(char **info);
int ls_execute(char **tokens);

#endif
