
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <sys/unistd.h>
#include "tracer.h"
#define UNIX_DOMAIN "/home/czl/learncoding/UNIX.domain"
 
int main(void)
{
	unsigned int connect_fd;
	unsigned int  ret;
	char snd_buf[1024];
	static struct sockaddr_un srv_addr;
	//create unix socket
	connect_fd = socket(PF_UNIX, SOCK_STREAM, 0);
	if(connect_fd < 0) {
		perror("cannot create communication socket");
		return 1;
	}
	srv_addr.sun_family = AF_UNIX;
	strcpy(srv_addr.sun_path,UNIX_DOMAIN);
	//connect server
	ret = connect(connect_fd, (struct sockaddr*)&srv_addr, sizeof(srv_addr));
	if(ret == -1) {
		perror("cannot connect to the server");	
		close(connect_fd);
		return 1;
	}
	char send_msg=0x01;
	char test_send[40]="test";
	
	Tracer tracer;
	tracer.startTime();
	printf("%d\n",sizeof(test_send));
	for(int i=0;i<1000000;i++){
		write(connect_fd,test_send,sizeof(test_send));
	}
	long runtime=tracer.getRunTime();
	printf("%ld\n",runtime);
	close(connect_fd);
	return 0;
}