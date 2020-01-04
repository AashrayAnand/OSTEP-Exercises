#include <stdio.h>
#include <unistd.h>

#include <sys/time.h>

#include <signal.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


// results: over time, the avg. time for open and write system
// calls falls dramatically, from about 40-50 microseconds for a
// single execution of the call, to about 19-20 microseconds on average
// when executed 100 times in a row
int main(){
    // structs to hold time info for before and after executing
    // various ssystem calls
    struct timeval preOpen, postOpen, preWrite, postWrite, preRead, postRead;    
    (void)gettimeofday(&preOpen, NULL);
    int ptr;
    for(int i = 0; i < 100; i++){
        ptr = open("file.txt", O_RDWR);
        if(ptr < 0){
            printf("error opening file");
            return -1;
        }
    }
    (void)gettimeofday(&postOpen, NULL);
    suseconds_t timeOpen = postOpen.tv_usec - preOpen.tv_usec; 
    double avg_time = timeOpen / 100.0;
    printf("avg. time (over 100 iterations) to call/check open(): %f\n", avg_time);

    char * data = "This is a random sentence to write to a file\n";
    int stringLen = sizeof(data) / sizeof(data[0]);
    (void)gettimeofday(&preWrite, NULL);
    int writeStatus;
    for(int i = 0; i < 100; i++){
        writeStatus = write(ptr, data, stringLen);
        if(writeStatus < 0){
          printf("error writing file");
          return -1;
        }
    }
    (void)gettimeofday(&postWrite, NULL);
    suseconds_t timeWrite = postWrite.tv_usec - preWrite.tv_usec;
    avg_time = timeWrite / 100.0;
    printf("time to call/check write(): %f\n", avg_time);

}
