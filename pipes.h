#ifndef __PIPES_IO_
#define __PIPES_IO_

int no_of_pipes_present(char **tokens);
int spawn_proc(int in, int out, char **tokens);
int fork_pipes(int n, char **commands_p);

#endif
