// I/O
#include <stdio.h>

// fork/exec/
#include <unistd.h>

// kill/signal
#include <signal.h>

#include <stdlib.h>

// open + file privilege constants
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(){
    // spawn child process
    int rc1 = fork();

    char *command = "/bin/ls";
    
    // environment of execution, for execle and execve
    char *env[] = { "HOME=/usr/bin", "LOGNAME=home", (char *)0 };

    if(rc1 < 0){
        printf("error forking process\n");
        return -1;
    } else if(rc1 == 0){
        // execle provides a path to the file to
        // be executed, as well as a list of the command
        // to be executed, and an environment for the
        // executing program to run in    
        execl(command, "ls",  NULL);

        //execle(command, "ls",  NULL, env);
        //execv(command, argv);
        // duplicates action of shell, only need to supply
        // command name, instead of path to file
        //execvp("ls", argv);
        // can supply command for same reason as execvp
        //execvpe("ls", argv, env);
    } else {
        // allow child process to terminate before continuing
        // parent process
        wait(NULL);
    }
    return 0;
}
