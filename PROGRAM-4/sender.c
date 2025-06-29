#include <sys/types.h> 
#include <sys/socket.h> 
#include <netinet/in.h> 
#include <arpa/inet.h> 
#include <time.h> 
#include <string.h> 
#include <stdio.h> 
#include<stdlib.h> 

int main(int argc, char *argv[]) 
{ 
struct sockaddr_in addr; 
int fd; 
char *message="RVCE-CSE"; 
  
fd=socket(AF_INET,SOCK_DGRAM,0);
memset(&addr,0,sizeof(addr)); 
addr.sin_family=AF_INET; 
addr.sin_addr.s_addr=inet_addr("225.0.0.37"); 
addr.sin_port=htons(12345); 

while(1){ 
   sendto(fd,message,sizeof(message),0,(struct sockaddr *) &addr,sizeof(addr));
   sleep(1); 
  } 
 return 0;
} 

/*
run listener first
cc sender.c -o sender
./sender
*/