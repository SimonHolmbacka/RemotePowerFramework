/* Sample UDP client */

#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdio.h>

int main(int argc, char**argv)
{
  int sockfd,n;
  struct sockaddr_in servaddr,cliaddr;
  char sendline[2] = {'s','t'};
  char recvline[1000];
  char str[50];
  if (argc < 3)
  {
    printf("usage:  udpcli <IP address> <name postfix>\n");
    exit(1);
  }

  sockfd=socket(AF_INET,SOCK_DGRAM,0);
  bzero(&servaddr,sizeof(servaddr));
  servaddr.sin_family = AF_INET;
  servaddr.sin_addr.s_addr=inet_addr(argv[1]);
  servaddr.sin_port=htons(32000);

  printf("Starting power measurements\n");
  /*system code here...*/
//  char str[10];
  //sprintf(str,"../Datalogger ../oDroid.config > power_%s.log &",argv[2]);
  //system(str);  
  system("../Datalogger ../oDroid.config > power.log &");
  
  printf("Sending start message\n");
  sendto(sockfd,sendline,strlen(sendline),0,(struct sockaddr *)&servaddr,sizeof(servaddr));

  int sockfd2,n2;
  struct sockaddr_in servaddr2,cliaddr2;
  socklen_t len;
  char mesg[1000];

  sockfd2=socket(AF_INET,SOCK_DGRAM,0);
  bzero(&servaddr2,sizeof(servaddr2));
  servaddr2.sin_family = AF_INET;
  servaddr2.sin_addr.s_addr=htonl(INADDR_ANY);
  servaddr2.sin_port=htons(32001);
  bind(sockfd2,(struct sockaddr *)&servaddr2,sizeof(servaddr2));
  printf("Waiting for measurements to finish...\n");
  
  for (;;)
  {
    len = sizeof(cliaddr2);
    n2 = recvfrom(sockfd2,mesg,1000,0,(struct sockaddr *)&cliaddr2,&len);
    printf("Got stop message\n");
    break;
  }
  /*Kill datalogger task here*/
  system("kill -9 `ps aux | grep Datalogger | awk '{print $2}'`");
  sprintf(str,"cp power.log power_%s.log",argv[2]);
  system(str);  
  printf("Power measurement done!\n");
  return 0;
}
