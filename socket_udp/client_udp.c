#include<stdio.h>
#include<unistd.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>

int main(){
    
    int sockCli = socket(AF_INET,SOCK_DGRAM,0);
    if (sockCli == -1){
        printf("create socket failed");
        return -1;
    }
    struct sockaddr_in addrSer;
    addrSer.sin_family = AF_INET;
    addrSer.sin_port = htons(5050);
    addrSer.sin_addr.s_addr = inet_addr("127.0.0.1");
    
    socklen_t addrlen = sizeof(struct sockaddr);
    
    char sendbuf[256];
    char recvbuf[256];
    
    while(1){
        printf("client :>");
        scanf("%s",sendbuf);
        sendto(sockCli,sendbuf,strlen(sendbuf)+1,0,(struct sockaddr *)&addrSer,addrlen);
        
        printf("receive server data ");
        
        recvfrom(sockCli,recvbuf,256,0,(struct sockaddr *)&addrSer,&addrlen);
        
        printf("client data = %s\n",recvbuf);
        
    }
    
    
    return 0;
}
