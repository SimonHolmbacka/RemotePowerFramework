
/* Sample UDP server */

#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>

int main(int argc, char**argv)
{
   if (argc != 2)
   {
      printf("usage:  udpcli <IP address>\n");
      exit(1);
   }
   int sockfd,n;
   struct sockaddr_in servaddr,cliaddr;
   socklen_t len;
   char mesg[10];
	 int i;
	 char sendline[2] = {'t','t'};

	printf("Listening...\n");
  int ind;   
  for (ind=0 ; ind<1 ; ind++){
   sockfd = 0;
	 n = 0;
	 for(i=0;i<10;i++)mesg[i] = '\0';

	 sockfd=socket(AF_INET,SOCK_DGRAM,0);
	 bzero(&servaddr,sizeof(servaddr));
	 servaddr.sin_family = AF_INET;
	 servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
	 servaddr.sin_port=htons(32000);
	 bind(sockfd,(struct sockaddr *)&servaddr,sizeof(servaddr));

    len = sizeof(cliaddr);
    n = recvfrom(sockfd,mesg,1000,0,(struct sockaddr *)&cliaddr,&len);
    mesg[n] = 0;
    printf("Received the following:");
    printf("%s",mesg);
		//break;
   
   printf("Starting test\n");
   //system("./hevc 240 300 4 0 0 0");
   system("sleep 3");
   sockfd=socket(AF_INET,SOCK_DGRAM,0);
   bzero(&servaddr,sizeof(servaddr));
   servaddr.sin_family = AF_INET;
   servaddr.sin_addr.s_addr=inet_addr(argv[1]);
   servaddr.sin_port=htons(32001);
   printf("Sending back reply\n");
   sendto(sockfd,sendline,strlen(sendline),0,(struct sockaddr *)&servaddr,sizeof(servaddr));
  }
}

