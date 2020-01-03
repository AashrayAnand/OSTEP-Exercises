// I/O
#include <stdio.h>

// fork/exec
#include <unistd.h>

// wait
#include <sys/types.h>
#include <sys/wait.h>

int main(){
    int rc = fork();
    if(rc < 0){
        printf("error forking process\n");
    } else if(rc == 0){
        // child process has no children, so if we call
        // wait (without passing the WNOHANG arg), then
        // the child process will never terminate, and as
        // a result, the parent process (waiting on the child
        // to complete) will also never terminate
        //wait(NULL);
    } else {
        // can use value of fork to specifically wait on
        // newly spawned child process, can be useful in
        // scenarios when we have forked multiple times and
        // want to wait on only one child
        int status;
        pid_t child = waitpid(rc, &status, 0);
        // wait returns PID of process that terminated
        printf("%d\n", child);
    }
    return 0;
}
