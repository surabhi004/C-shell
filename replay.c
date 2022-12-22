#include "headers.h"
#include "executing_commands.h"

void replay(char **tokens)
{

    // replay -command echo "hi" -interval 3 -period 6
    int args = no_of_strings(tokens);
    if (args < 7)
    {
        printf("Too few arguments\n");
        return;
    }

    if (strcmp(tokens[1], "-command") != 0)
    {
        printf("replay command is typed incorrectly\n");
        return;
    }

    //make the new command
    char **modified_command = malloc(100);
    modified_command = tokens;

    int j = 0;
    for (int i = 2; i < args - 4; i++)
    {
        modified_command[j] = tokens[i];
        j++;
    }
    modified_command[j] = NULL;
    // print_tokens(modified_command);

    int x = atoi(tokens[args - 1]);
    int z = atoi(tokens[args - 3]);
    int y = x / z;

    for (int i = 0; i < y; i++)
    {
        execute_all(modified_command);
        sleep(z);
    }
}