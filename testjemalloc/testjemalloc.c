#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define THREAD_NUM 10
#define TEST_NUM 10000000

struct timeval startTime;
unsigned long runTime;

char *p[THREAD_NUM][TEST_NUM];

unsigned long getRunTime(struct timeval begTime) {
    struct timeval endTime;
    mingw_gettimeofday(&endTime, NULL);
    unsigned long duration = (endTime.tv_sec - begTime.tv_sec) * 1000000 + endTime.tv_usec - begTime.tv_usec;
    begTime = endTime;
    return duration;
}

void do_malloc(int i){
    //printf("th %d start\n",i);
    for(int j=0;j<TEST_NUM;j++){
        p[i][j]=malloc(80);
    }
    //printf("th %d finish\n",i);
}

int main(){
    pthread_t pt[THREAD_NUM];
    int ret;
    mingw_gettimeofday(&startTime,NULL);
    for(int i=0;i<THREAD_NUM;i++){
        if(pthread_create(&pt[i],NULL,(void *)&do_malloc,i)!=0){
            printf("create thread fail\n");
            return 0;
        }
    }
    for(int i=0;i<THREAD_NUM;i++){
        if(pthread_join(pt[i],NULL)!=0){
            printf("cannot join\n");
        }else{
            printf("%d join\n",i);
        }
    }
    runTime=getRunTime(startTime);
    printf("finished in %lu\n",runTime);
}