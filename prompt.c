#include "prompt.h"
#include "headers.h"

char *getUserName()
{
  uid_t uid = geteuid();
  struct passwd *pw = getpwuid(uid);
  if (pw)
  {
    return pw->pw_name;
  }

  return "";
}

void prompt(char *home_direc)
{
  char *arg1 = get_system_name();
  char *arg2 = find_final_path(get_cwd_path(), home_direc);

  printf("%s@%s:%s$ ", getUserName(), arg1, arg2);
}
