#include <cstdio>
#include <cstdlib>
#include "tracer.h"
#define TEST_NUM 1000000
Tracer tracer[4];
long runTime[4];
void * p[TEST_NUM];
int main(){
    timeval t1,t2;
    tracer[0].startTime();
    for(int i=0;i<TEST_NUM;i++){
        gettimeofday(&t1,NULL);
        gettimeofday(&t2,NULL);
    }
    runTime[0]+=tracer[0].getRunTime();
    
    printf("%ld\n",runTime[0]);
    

}