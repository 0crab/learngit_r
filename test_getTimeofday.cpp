#include <cstdio>
#include <cstdlib>
#include "tracer.h"
#define TEST_NUM 1000000
Tracer tracer[4];
long runTime[4];

//void * p[TEST_NUM];
unsigned long getRunTime(struct timeval begTime) {
    struct timeval endTime;
    gettimeofday(&endTime, NULL);
    unsigned long duration = (endTime.tv_sec - begTime.tv_sec) * 1000000 + endTime.tv_usec - begTime.tv_usec;
    begTime = endTime;
    return duration;
}

int main(){
    timeval t1,t2;
    unsigned long runtime;
    tracer[0].startTime();
    for(int i=0;i<TEST_NUM;i++){
        gettimeofday(&t1,NULL);
        runtime=getRunTime(t1);
    }
    runTime[0]+=tracer[0].getRunTime();
    
    printf("%ld\n",runTime[0]);
}