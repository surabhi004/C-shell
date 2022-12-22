#include "prompt.h"
#include "functions.h"
#include "headers.h"
#include "executing_commands.h"
#include "other_builtins.h"
#include "pipes.h"
#include "signal_handling.h"

// static sigjmp_buf env;
// bgp_count = 0;

void sigint_handler(int signo)
{
    siglongjmp(env, 42);
}

int main()
{

    // signal(SIGINT, SIG_IGN);
    signal(SIGINT, sigint_handler);
    // signal(SIGTSTP, sigint_handler);

    signal(SIGTSTP, SIG_IGN);

    //the home directory
    char *home_dir_buf;
    char *hd_path = get_cwd_path();
    char *home_dir = get_dir(hd_path);

    // //this array holds all the commands if they are seperated by ;
    char **commands = malloc(200 * sizeof(char *));
    char **commands_p = malloc(200 * sizeof(char *));

    // //this array holds the command and all its options
    char **command_tokens = malloc(200 * sizeof(char *));
    last_cd_input = malloc(250);
    last_cd_input = get_cwd_path();

    // signals();
    // signal(SIGINT, sigint_handler);
    // signal(SIGTSTP, sigtstp_handler);

    while (1)
    {

        if (sigsetjmp(env, 1) == 42)
        {
            printf("CTRL C PRESSED\n");
        }
        prompt(home_dir);

        char *userInput = malloc(200 * sizeof(char));

        // //this array holds all the commands if they are seperated by ;
        // char **commands = malloc(200 * sizeof(char *));
        // char **commands_p = malloc(200 * sizeof(char *));

        // // //this array holds the command and all its options
        // char **command_tokens = malloc(200 * sizeof(char *));
        //changes from here--------
        char *buffer;
        size_t bufsize = 100;
        size_t characters;

        buffer = (char *)malloc(bufsize * sizeof(char));
        if (buffer == NULL)
        {
            perror("Unable to allocate buffer");
            exit(1);
        }

        characters = getline(&buffer, &bufsize, stdin);

        strcpy(userInput, buffer);
        // userInput = getline_t();

        //removes "\n" from when we press enter key
        if (characters == -1)
        {
            printf("\n");
            exit(0);
        }

        //if user input spaces and then enter
        char *check = malloc(50);
        strcpy(check, buffer);
        char **check_t = malloc(50);
        check_t = tokenize(check, " ");
        if (strcmp(check_t[0], "\n") == 0)
        {
            continue;
        }

        if (strcmp(userInput, "\n") == 0)
        {
            continue;
        }
        //tokennize with space and \n
        char *t1;
        if ((t1 = strrchr(userInput, '\n')) != NULL)
        {
            *t1 = 0;
        }
        commands = tokenize(userInput, ";");

        if (strcmp(commands[0], "exit") == 0)
        {
            break;
        }
        int no_of_commands = no_of_strings(commands);
        for (int i = 0; i < no_of_commands; i++)

        {
            command_tokens = tokenize(commands[i], " \t");

            int no_of_pipes = no_of_pipes_present(command_tokens);

            if (no_of_pipes > 0)
            {
                //cpmmands seperate by "|"
                // printf("no of pipes--%d\n", no_of_pipes);
                char **commands_p = malloc(250);
                commands_p = tokenize(commands[i], "|");
                // printf("tokenized wrt |\n");

                fork_pipes(no_of_pipes, commands_p);
                // printf("forked pipes\n");
                free(commands_p);
            }
            else
            {
                // command_tokens = tokenize(commands[i], " \t");
                execute_all(command_tokens);
            }

            // command_tokens = tokenize(commands[i], " \t");
            // execute_all(command_tokens);
            // return 0;
            // exit(0);
            // fflush(NULL);
        }

        char *temp_c = get_cwd_path();
        strcpy(last_cd_input, temp_c);
        // free(command_tokens);
        // free(last_cd_input);
        // free(commands_p);
    }
    free(commands);

    free(command_tokens);
    free(last_cd_input);
    // free(commands_p);

    return 0;
}
