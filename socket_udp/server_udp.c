#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>

int main(){
    int sockSer = socket(AF_INET,SOCK_DGRAM,0);
    if (sockSer == -1){
        printf("create socket error");
        return -1;
    }
    struct sockaddr_in addrSer;
    addrSer.sin_family = AF_INET;
    addrSer.sin_port = htons(5050);
    addrSer.sin_addr.s_addr = inet_addr("127.0.0.1");
    
    socklen_t addrlen = sizeof(struct sockaddr);
    int res = bind(sockSer,(struct sockaddr*)&addrSer,addrlen);
    if (res == -1){
        printf("bind failed");
        return -1;
    }
    //测试收发
    char sendbuf[256];
    char recvbuf[256];
    struct sockaddr_in addrCli;
    while(1){
        recvfrom(sockSer,recvbuf,256,0,(struct sockaddr *)&addrCli,&addrlen);
        printf("client = %s \n",recvbuf);
        
        printf("ser :>");
        scanf("%s",sendbuf);
        sendto(sockSer,sendbuf,strlen(sendbuf)+1,0,(struct sockaddr*)&addrCli,addrlen);
    }
    
    	
	
    return 0;
	
}
