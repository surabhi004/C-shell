#ifndef __CD_FUNC
#define __CD_FUNC

//checks if the working directory has the home directory(directory where the shell executable resides)
//if it contains the home dircetory,it returns the path of the given directory relative to the home directory
//otherwise return NULL
char *check(char *curr_path, char *home_dir);

//if it contains the home directory,it returns the path of the given directory relative to the home directory
//otherwise returns absolute path
char *find_final_path(char *dir_or_path, char *home_dir);

//changes the current working directory to the dir_or_path dir
int change_dir(char *dir_or_path, char *last_cd_input);

#endif