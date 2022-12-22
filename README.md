# SHELL
ROLL NO - 2021121004

## Compile
```sh
make main
```

## Run the shell
```sh
./a.out
```

## Exit the Shell
```sh
To exit the shell,use either of the following

1. Type exit on the prompt
2. Use CTRL + D 
```


Current directory of shell is set to be the home directory.


This shell implements the following commands seperately.
### ***Built in commands***

>ls


```sh
> FILE - ls.c
- ls
- ls -a
- ls -l
- ls .
- ls ..
- ls ~
- ls -a -l
- ls -la / ls -al
- ls <Directory/File_name>
- ls -<flags> <Directory/File_name>
- ls -l <dir_1> -a <dir_2>
- ls -la <dir_1> <dir_2>
```


 
>cd
```sh
> FILE - cd.c 
- Changes the directory to the path or directory specified in the argument
```
>pwd
```sh
> FILE - other_builtins.c - (pwd_x)
- Prints working directory
```


>echo
```sh
>FILE - other_builtins.c - (echo_x)
```


>pinfo   
```sh
> FILE - pinfo.c - (pinfo_x)
-pinfo: This prints the process-related info of your shell program. 
-pinfo <pid>: This prints the process info about the given PID.
```


>repeat
```sh
FILE - repeat.c - (repeat_x)
The command is responsible for executing the given
instruction multiple times. The first argument to the command specifies the number of
times the following command is to be run. 
Example - repeat 3 echo hello
```

>replay
```sh
FILE - replay.c 
This command executes a particular command in fixed time interval for a certain period.
Example:
replay -command echo "hi" -interval 3 -period 6
This command executes echo "hi" command after every 3 seconds until 6 seconds are elapsed.
```



>fg
```sh
Takes the job number assigned by the shell of a running job and sends the signal corresponding to signal number to that process. 
```

>bg
```sh
Changes the state of a stopped background job to running (in the background).Does nothing if the job is already running in the background.
```
>sig
```sh
Takes the job number (assigned by your shell) of a running job and sends the signal corresponding to signal number to that process. 
```

>jobs
```sh
This command prints a list of all currently running background processes spawned by the shell in alphabetical order of the command name, along with
their job number (a sequential number assigned by your shell), process ID and their state, which can either be running or stopped. Flags can be specified
as well. If the flag specified is -r, it prints only the running processes else if the flag is -s ,it prints the stopped processes only.
```

**1. CTRL-Z 
Pushs any currently running foreground job into the background, and change its state from running to stopped. 
Has no effect on the shell if there is no foreground process running.**

**2. CTRL-C 
It interrupts any currently running foreground job, by sending it the SIGINT signal.
It has no effect on the shell if there is no foreground
process running.**

**3. CTRL-D 
It logs you out of your shell, without having any effect on the actual terminal.**


Redirection is handled

Processes can be run in background using "&" after the process name.

Background processs is not handled in the redirection implementation

To run multiple commans on a single line seperate commands using ";"
 
### ***The files***

main.c-The main function of the program

prompt.c  -  the prompt functionality of the shell , displays what to display on the prompt

functions.c - contains helper functions for implementation of the different commands

ls.c - ls command implementation

cd.c  - cd command implementation

other_builtins.c - contains code for echo command and pwd command

pinfo.c - implements the pinfo command

repeat.c - implements the repeat command

executing_commands.c - contains the main logic for implementing the different commands, implementing different commands in the background and foreground

replay.c - implements replay command

fg.c - implements fg command

bg.c - implements bg command

sig.c - implements sig command

redirection.c - has functions to handle redirection

jobs.c - impleemnst jobs command

pipes.c - handles pipes in the commands