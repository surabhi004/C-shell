#ifndef __X
#define __X

//Gets user input
char *getline_t();

//tokenizes the input string with respect to the delimiter
char **tokenize(char *input, char *delimiter);

//gets the absolute path of a file
char *get_absolute_path(char *s);

//counts the no of strings in the (char**)array of strings
int no_of_strings(char **x);

//print the elements of the array of strings
void print_tokens(char **s);

char *get_dir(char *abs_path);

//gets the current working directory path-if invoked from the shell program's home directory
//it return relative path otherwise it returns absolute path
char *get_cwd_path();
char *get_system_name();
void print_bpg_pids(int bgp_pids[]);
int compare_job_names(const void *j1_name, const void *j2_name);

#endif