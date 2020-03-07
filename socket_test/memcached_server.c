#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <sys/unistd.h>

#define UNIX_DOMAIN "/home/czl/memcached.sock"

#define READ_FROM_CLIENT 0X01
#define WRITE_TO_CLIENT 0x02

int main(void)
{
    socklen_t clt_addr_len;
    socklen_t listen_fd;
    socklen_t com_fd;
    socklen_t ret;
    //int i;
    static char data_buf[1024];
    socklen_t len;
    struct sockaddr_un clt_addr;
    struct sockaddr_un srv_addr;
    listen_fd = socket(PF_UNIX, SOCK_STREAM, 0);
    if(listen_fd < 0) {
        perror("cannot create communication socket");
        return 1;
    }
    //set server addr_param
    srv_addr.sun_family = AF_UNIX;
    strcpy(srv_addr.sun_path,UNIX_DOMAIN);
    unlink(UNIX_DOMAIN);
    //bind sockfd & addr
    ret = bind(listen_fd, (struct sockaddr*)&srv_addr, sizeof(srv_addr));
    if(ret == -1) {
        perror("cannot bind server socket");
        close(listen_fd);
        unlink(UNIX_DOMAIN);
        return 1;
    }
    //listen sockfd
    ret = listen(listen_fd,1);
    if(ret == -1) {
        perror("cannot listen the client connect request");
        close(listen_fd);
        unlink(UNIX_DOMAIN);
        return 1;
    }
    int count=0;
    while(1) {
        int read_rt;
        //have connect request use accept
        len = sizeof(clt_addr);
        com_fd = accept(listen_fd,(struct sockaddr*)&clt_addr,&len);
        if(com_fd < 0) {
            perror("cannot accept client connect request");
            close(listen_fd);
            unlink(UNIX_DOMAIN);
            return 1;
        }


        char rec_buff[48];
        int count=0;
        for(int i=0;i<1000000;i++){
            memset(rec_buff,0,sizeof(rec_buff));
            read_rt=read(com_fd,rec_buff,sizeof(rec_buff));
            //printf("rec %d bytes:%s\n",read_rt,rec_buff);
            if(read_rt==48)
                count++;
        }
        printf("%d\n",count);
    }

    close(listen_fd);
    unlink(UNIX_DOMAIN);
    return 0;
}