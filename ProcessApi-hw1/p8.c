#include <stdio.h>
#include <unistd.h>

#include <signal.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(){
    int p[2];
    if(pipe(p) < 0){
        printf("error creating pipe\n");
    }

    int rc = fork();
    if(rc < 0){
        printf("error forking process\n");
    } else if (rc == 0){
        // set stdout of first child to be write end
        // of the pipe
        printf("hello world from child 1\n");
        close(p[0]);
        dup2(p[1], 1);
        printf("hello pipe\n");
    } else {
        int rc2 = fork();
        if(rc2 < 0){
            printf("error forking process\n");
            return -1;
        } else if(rc2 == 0){
            printf("hello world from child 2\n");  
            // second child is receiving input only
            close(p[1]);
            // set standard in of second child to be
            // read end of pipe
            dup2(p[0], 0);

            char buffer[512];
            read(STDIN_FILENO, buffer, 512);
            printf("%s", buffer);
        }
    }
    return 0;
}
