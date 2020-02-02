#include <cstdio>
#include <cstdlib>
#include "tracer.h"
#define TEST_NUM 1000000
Tracer tracer[4];
long runTime[4];
void * p[TEST_NUM];
int main(){
    
    tracer[0].startTime();
    for(int i=0;i<TEST_NUM;i++){
        p[i]=malloc(80);
    }
    runTime[0]+=tracer[0].getRunTime();
    
    tracer[1].startTime();
    for(int i=0;i<TEST_NUM;i++){
        free(p[i]);
    }
    runTime[1]+=tracer[1].getRunTime();
    printf("malloc time:%ld\n",runTime[0]);
    printf("free time:%ld\n",runTime[1]);

}