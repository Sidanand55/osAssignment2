#include <stdio.h>
#include <stdlib.h>
#include<unistd.h>
#include <string.h>
#include <pthread.h>
#include <sched.h>
#include <time.h>
#include <math.h>
#include <wait.h>
#include <sys/wait.h>


int pid;
void func1(){   
    struct timespec start;
    struct timespec end;

    long long int nanosec1;
    long long int sec1;

    clock_gettime(CLOCK_BOOTTIME, &start);
   

    if(pid ==0){
        char source[20];

        sprintf(source, "%d", getpid());

        char destination[200]= "chrt -f -p 15";

        strcat(destination, source);

        system(destination);

        char* desti[2]= {NULL};
        execvp("./kernel.sh",desti);
    }
    


    clock_gettime(CLOCK_BOOTTIME,&end);
    
    
    nanosec1= end.tv_nsec- start.tv_nsec;
    sec1= end.tv_sec- start.tv_sec;

    printf("The elapsed for process1: %.2f \n", sec1 + nanosec1*1e-9);

}

void func2(){
    struct timespec start;
    struct timespec end;

    long long int nanosec2;
    long long int sec2;

    clock_gettime(CLOCK_BOOTTIME, &start);
    pid_t pid2= fork();
  

    if(pid ==0){
        char source[20];

        sprintf(source, "%d", getpid());

        char destination[200]= "chrt -f -p 20";

        strcat(destination, source);

        system(destination);

        char* desti[2]= {NULL};
        execvp("./kernel.sh",desti);
    }


    clock_gettime(CLOCK_BOOTTIME,&end);
    
    
    nanosec2= end.tv_nsec- start.tv_nsec;
    sec2= end.tv_sec- start.tv_sec;

    printf("The elapsed for process2: %.2f \n", sec2+ nanosec2*1e-9);

}


void func3(){
    struct timespec start;
    struct timespec end;

    long long int nanosec3;
    long long int sec3;

    clock_gettime(CLOCK_BOOTTIME, &start);
    pid_t pid3= fork();
  

    if(pid ==0){
        char source[20];

        sprintf(source, "%d", getpid());

        char destination[200]= "chrt -f -p 10";

        strcat(destination, source);

        system(destination);

        char* desti[2]= {NULL};
        execvp("./kernel.sh",desti);
    }


    clock_gettime(CLOCK_BOOTTIME,&end);
    
    
    nanosec3= end.tv_nsec- start.tv_nsec;
    sec3= end.tv_sec- start.tv_sec;

    printf("The elapsed for process3: %.2f \n", sec3 + nanosec3*1e-9);
}


int main(){

    func1();
    func2();
    func3();

    while(wait(NULL)>0){
        
    }




}