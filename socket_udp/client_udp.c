#include<stdio.h>
#include<unistd.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <errno.h>
#include <pthread.h>


struct sockaddr_in addrSer;
int sockSer = -1;

static void *readLoop();
static void *sendLoop();

static void *readLoop(){
    char recvbuf[256];
    socklen_t addrlen =sizeof(struct sockaddr) ;
    int count =0;
    while(1){
        count = recvfrom(sockSer,recvbuf,256,0,(struct sockaddr *)&addrSer,&addrlen);
        printf("recvfrom addrser port %d ,addr = %s\n",addrSer.sin_port,inet_ntoa (addrSer.sin_addr));
        printf("receeve server: %s \n",recvbuf);
        if (count < 0){
            printf("error :%s\n",strerror(errno));
            break;
        }
        
        
    }
    printf("error :%s\n",strerror(errno));
}

static void *sendLoop(){
    char sendbuf[256]="I am client,how are you ?";
    socklen_t addrlen = sizeof(struct sockaddr);
    while(1){
        
        sendto(sockSer,sendbuf,strlen(sendbuf),MSG_DONTWAIT,(struct sockaddr*)&addrSer,addrlen);
        printf("sendto addrser port %d ,addr = %s\n",addrSer.sin_port,inet_ntoa (addrSer.sin_addr));
        sleep(5);// send data per 5 seconds
    }
}

int main(){
    
    pthread_t clientReadThread ;
    pthread_t clientWriteThread;
    sockSer = socket(AF_INET,SOCK_DGRAM,0);
    if (sockSer == -1){
        printf("create socket failed");
        return -1;
    }
    
    addrSer.sin_family = AF_INET;
    addrSer.sin_port = htons(5050);
    addrSer.sin_addr.s_addr = inet_addr("127.0.0.1");
    
    socklen_t addrlen = sizeof(struct sockaddr);
    
    int n = pthread_create(&clientReadThread,NULL,readLoop,NULL);
    if (n==0){
        printf("create thread success\n");
    }else {
        printf("craete thread failed\n");
    }
    
    pthread_create(&clientWriteThread,NULL,sendLoop,NULL);
    
    pthread_join(clientReadThread,NULL);
    pthread_join(clientWriteThread,NULL);
 
    
#ifdef test
    char sendbuf[256];
    char recvbuf[256];
    
    while(1){
        printf("client :>");
        scanf("%s",sendbuf);
        sendto(sockCli,sendbuf,strlen(sendbuf),0,(struct sockaddr *)&addrSer,addrlen);
        
        printf("Server:");
        
        recvfrom(sockCli,recvbuf,256,0,(struct sockaddr *)&addrSer,&addrlen);
        
        printf("%s\n",recvbuf);
        
    }
#endif
    
    
    return 0;
}
