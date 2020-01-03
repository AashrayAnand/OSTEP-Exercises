#include <stdio.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

// result: both parent and child have access
// to the same file descriptors, as a file descriptor
// which was initialized before the fork() was
// available to be written to by both the
// parent, as well as the child

int main(){
    int fd = open("data2.txt", O_RDWR);
    if(fd < 0){
        printf("error opening file\n");
        return -1;
    }
    int rc = fork();
    if(rc < 0){
        printf("error forking new process\n");
        return -1;
    } else if(rc == 0){
        dprintf(fd, "child process here\n");
    } else {
        dprintf(fd, "parent process here\n");
    }
    return 0;
}
