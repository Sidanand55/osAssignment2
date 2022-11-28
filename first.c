#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<math.h>
#include <sched.h>
#include <time.h>
#include <pthread.h>

pthread_t thread1;
pthread_t thread2;
pthread_t thread3;

struct sched_param p1;
struct sched_param p2;
struct sched_param p3;




void *test_func2(){
    struct timespec t1;
    struct timespec t2;
    
    struct sched_param parameter2;
    parameter2.sched_priority= 90;
    pthread_setschedparam(thread2,SCHED_FIFO,&parameter2);
    clock_gettime(CLOCK_BOOTTIME, &t1);
    
    
    int c=0;
    for(long int i=0;i<pow(2,32);i++){
        c++;
    }
    clock_gettime(CLOCK_BOOTTIME, &t2);
    long sec= t2.tv_sec- t1.tv_sec;
    long long int nanosec= t2.tv_nsec - t1.tv_nsec;

    printf("Time elapsed of 2: %.2f seconds \n", sec + nanosec *1e-9);

}

void *test_func1(){ 
    
    struct timespec t1;
    struct timespec t2;

    struct sched_param parameter1;
    parameter1.sched_priority= 50;
    pthread_setschedparam(thread1,SCHED_OTHER,&parameter1); 
    clock_gettime(CLOCK_BOOTTIME, &t1);

    int c=0;
     for(long int i=0;i<pow(2,32);i++){
        c++;
    }

    clock_gettime(CLOCK_BOOTTIME, &t2);
    long sec= t2.tv_sec- t1.tv_sec;
    long long int nanosec= t2.tv_nsec - t1.tv_nsec;

    printf("Time elapsed of 1: %.2f seconds \n", sec + nanosec *1e-9);
    


}

void *test_func3(){
    struct timespec t1;
    struct timespec t2;
    
    struct sched_param parameter3;
    parameter3.sched_priority= 0;
    pthread_setschedparam(thread3,SCHED_RR,&parameter3);
    clock_gettime(CLOCK_BOOTTIME, &t1);
    
    int c=0;
     for(long int i=0;i<pow(2,32);i++){
        c++;

    }
    clock_gettime(CLOCK_BOOTTIME, &t2);
    long sec= t2.tv_sec- t1.tv_sec;
    long long int nanosec= t2.tv_nsec - t1.tv_nsec;

    printf("Time elapsed of 3: %.2f seconds \n", sec + nanosec *1e-9);
}





int main(){

    pthread_attr_t attribute1;
    pthread_attr_t attribute2;
    pthread_attr_t attribute3;

    pthread_attr_init(&attribute1);
    pthread_attr_setschedpolicy(&attribute1, SCHED_FIFO);
    pthread_attr_setschedparam(&attribute1, &p1);
    pthread_attr_setinheritsched(&attribute1,PTHREAD_INHERIT_SCHED);



    pthread_attr_init(&attribute2);
    pthread_attr_setschedpolicy(&attribute2, SCHED_RR);
    pthread_attr_setschedparam(&attribute2, &p2);
    pthread_attr_setinheritsched(&attribute2,PTHREAD_INHERIT_SCHED);


    pthread_attr_init(&attribute3);
    pthread_attr_setschedpolicy(&attribute3, SCHED_OTHER);
    pthread_attr_setschedparam(&attribute3, &p3);
    pthread_attr_setinheritsched(&attribute3,PTHREAD_INHERIT_SCHED);


    if(pthread_create(&thread3 , &attribute3, &test_func3, NULL)!=0){
        return 0;
    }
    
    if(pthread_create(&thread2 , &attribute2, &test_func2, NULL)!=0){
        return 0;
    }
    

     if(pthread_create(&thread1, &attribute1, &test_func1, NULL)!=0){
        return 0;
    }
    
    if(pthread_join(thread1,NULL)!=0){
        return 0;
    }
    if(pthread_join(thread2,NULL)!=0){
        return 0;
    }
    if(pthread_join(thread3,NULL)!=0){
        return 0;
    }

    return 0;
    
}
