/* Time measurement module */
#include <sys/time.h>
#include <stdio.h>
#include <pthread.h>
#define DATA_NUM 1000000
#define THREAD_NUM 1
#define INDEX_HASH_SIZE 100
#define uint64_t unsigned long


struct myHashItem{
    int fd;
    int index;
};
struct myHashItem indexHashTable[INDEX_HASH_SIZE];
int fd_num;

struct timeval startTime[4][THREAD_NUM];
uint64_t myRuntime[4][THREAD_NUM];
uint64_t myCount=0;

uint64_t getRunTime(struct timeval begTime) {
    struct timeval endTime;
    gettimeofday(&endTime, NULL);
    uint64_t duration = (endTime.tv_sec - begTime.tv_sec) * 1000000 + endTime.tv_usec - begTime.tv_usec;
    begTime = endTime;
    return duration;
}

int get_index_from_hashtable(int fd){
    int i=fd%INDEX_HASH_SIZE;
    while (indexHashTable[i].fd!=0&&indexHashTable[i].fd!=fd){
        i=(i+1)%INDEX_HASH_SIZE;
    }
    if(indexHashTable[i].fd==0) return -1;
    else    return indexHashTable[i].index;
}
//verify that fd is not in indexHashTable before calling
int insert_index_to_hashtable(int fd,int index){
    int i=fd%INDEX_HASH_SIZE;
    while (indexHashTable[i].fd!=0){
        i=(i+1)%INDEX_HASH_SIZE;
    }
    indexHashTable[i].fd=fd;
    indexHashTable[i].index=index;
}

int get_index(int fd){
    int index=get_index_from_hashtable(fd);
    if(index==-1){
        if(fd_num>=THREAD_NUM){
            printf("error:too many fd\n");
            return -1;
        }else{
            insert_index_to_hashtable(fd,fd_num++);
            return fd_num-1;
        }
    }else{
        return index;
    }
}
void get_start_time(int time_index,int fd){
    int index=get_index(fd);
    if(index==-1){
        printf("index error\n");
        fflush(stdout);
    }
    gettimeofday(&startTime[time_index][index],NULL);
}
void get_run_time(int time_index,int fd){
    int index=get_index(fd);
    if(index==-1){
        printf("index error\n");
        fflush(stdout);
    }
    myRuntime[time_index][index]+=getRunTime(startTime[time_index][index]);
}

void show_test_time(){
    printf("--------------\n");
    fflush(stdout);
    uint64_t time[4];
    for(int i=0;i<4;i++) time[i]=0;
    for(int i=0;i<4;i++){
        for(int j=0;j<THREAD_NUM;j++){
            time[i]+=myRuntime[i][j];
        }
        time[i]/=THREAD_NUM;
        printf("time %d :%lu\n",i,time[i]);
        fflush(stdout);
    }
    for(int i=0;i<4;i++){
        for(int j=0;j<THREAD_NUM;j++){
            myRuntime[i][j]=0;
        }
    }
}

int main(){
    struct timeval sttime;
    unsigned long runtime;
    gettimeofday(&sttime,NULL);
    for(int i=0;i<DATA_NUM;i++){
        for(int j=5;j<THREAD_NUM+5;j++){
            get_start_time(0,j);
            get_run_time(0,j);
            get_start_time(1,j);
            get_run_time(1,j);
            get_start_time(2,j);
            get_run_time(2,j);
            get_start_time(3,j);
            get_run_time(3,j);
        }
    }
    runtime=getRunTime(sttime);
    printf("%lu\n",runtime);
}