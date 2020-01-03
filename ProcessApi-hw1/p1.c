#include <stdio.h>
#include <unistd.h>

// result: child x = 11
//         parent x = 12
// can conclude that the address
// spaces of the processes are 
// indeed different, and that modifying
// variables in one doesn't affect the other

int main(){
    int x = 10;
    int rc = fork();
    // child condition
    if(rc == 0){
        x += 1;
        printf("child process: x = %d\n", x);
    } else {
        x += 2;
        printf("parent process: x = %d\n", x);
    }
    return 0;
}
