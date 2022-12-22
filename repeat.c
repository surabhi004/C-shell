#include "headers.h"
#include "executing_commands.h"

void repeat_x(char **tokens)
{
    char **new_tokens = malloc(250);
    int no = atoi(tokens[1]);
    int j = 0;

    for (int i = 2; tokens[i] != NULL; i++)
    {
        new_tokens[j] = malloc(50);
        strcpy(new_tokens[j], tokens[i]);

        j++;
    }
    new_tokens[j] = NULL;

    for (int i = 0; i < no; i++)
    {
        execute_all(new_tokens);
    }
    free(new_tokens);
}
