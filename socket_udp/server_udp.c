#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <errno.h>
#include <pthread.h>
struct sockaddr_in addrSer;
struct sockaddr_in addrCli;
int sockSer = -1;

static void *readLoop();
static void *sendLoop();


static void *readLoop(){
    char recvbuf[256];
    
    socklen_t addrlen = sizeof(struct sockaddr);
    int count =0;
    while(1){
        count = recvfrom(sockSer,recvbuf,256,0,(struct sockaddr *)&addrCli,&addrlen);
        printf("receeve client: %s \n",recvbuf);
        if (count < 0){
            printf("error :%s\n",strerror(errno));
            break;
        }
        
        
    }
    printf("error :%s\n",strerror(errno));
    
}

static void *sendLoop(){
    
    char sendbuf[256]="I am server,how are you?";
    
    socklen_t addrlen = sizeof(struct sockaddr);
    while(1){
        sendto(sockSer,sendbuf,strlen(sendbuf),MSG_DONTWAIT,(struct sockaddr*)&addrCli,addrlen);
        sleep(5);// send data per 5 seconds
    }
    
}
int main(){
    pthread_t serverReadThread ;
    pthread_t serverWriteThread;
    sockSer = socket(AF_INET,SOCK_DGRAM,0);
    if (sockSer == -1){
        printf("create socket error");
        return -1;
    }
    
    addrSer.sin_family = AF_INET;
    addrSer.sin_port = htons(5050);
    addrSer.sin_addr.s_addr = inet_addr("127.0.0.1");
    
    socklen_t addrlen = sizeof(struct sockaddr);
    int res = bind(sockSer,(struct sockaddr*)&addrSer,addrlen);
    if (res == -1){
        printf("bind failed");
        return -1;
    }
    printf("start server read & send\n");
    pthread_create(&serverReadThread,NULL,readLoop,NULL);
    pthread_create(&serverWriteThread,NULL,sendLoop,NULL);
    
    pthread_join(serverReadThread,NULL);
    pthread_join(serverWriteThread,NULL);
#if 0
    
    //测试收发
    char sendbuf[256];
    char recvbuf[256];
    struct sockaddr_in addrCli;
    while(1){
        recvfrom(sockSer,recvbuf,256,0,(struct sockaddr *)&addrCli,&addrlen);
        printf("client: %s \n",recvbuf);
        
        printf("input->");
        scanf("%s",sendbuf);
        sendto(sockSer,sendbuf,strlen(sendbuf)+1,0,(struct sockaddr*)&addrCli,addrlen);
    }
#endif
    	
	
    return 0;
	
}



