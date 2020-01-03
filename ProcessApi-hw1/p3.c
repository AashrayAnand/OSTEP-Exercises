#include <stdio.h>
#include <unistd.h>

#include <signal.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

// solution: although we can wait
// on the child process to print goodbye
// in the parent process, we can also utilize
// signals, and have
//
//

void handler(){
    printf("goodbye\n");
}

int main(){
    // get parent PID, to issue signal
    // from child process
    int pid = getpid();
    int rc = fork();
    if(rc < 0){
        printf("error forking new proces\n");
        return -1;
    } else if(rc == 0){
        printf("hello\n");
        kill(pid, SIGINT);
    } else {
        // 
        signal(SIGINT, handler);
        // wait indefinitely for SIGCONT signal
        pause();
    }
    return 0;
}
