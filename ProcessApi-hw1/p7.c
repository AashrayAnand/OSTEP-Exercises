#include <stdio.h>
#include <unistd.h>

#include <signal.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


// result: if a child closes a file descriptor, then
// this file descriptor can no longer be written to by the child
// , however, the parent can still write to this file descriptor,
// this implies that the file descriptors are not shared by the
// processes, but are seemingly references to the same file
// descriptor

int main(){
    int rc = fork();
    if(rc < 0){
        printf("error forking process\n");
    } else if(rc == 0){
        close(STDOUT_FILENO);
        dprintf(STDOUT_FILENO, "will this work?\n");
    } else {
        dprintf(STDOUT_FILENO, "will this work??\n");
    }
}
