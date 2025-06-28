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
int fd, nbytes,addrlen,bufsize=25;
struct ip_mreq mreq; 
char buf[25]; 
u_int yes=1;          

fd=socket(AF_INET,SOCK_DGRAM,0);
setsockopt(fd,SOL_SOCKET,SO_REUSEADDR,&yes,sizeof(yes));

memset(&addr,0,sizeof(addr)); 
addr.sin_family=AF_INET; 
addr.sin_addr.s_addr=htonl(INADDR_ANY); 
addr.sin_port=htons(12345); 
bind(fd,(struct sockaddr *) &addr,sizeof(addr));

mreq.imr_multiaddr.s_addr=inet_addr("225.0.0.37"); 
mreq.imr_interface.s_addr=htonl(INADDR_ANY); 

setsockopt(fd,IPPROTO_IP,IP_ADD_MEMBERSHIP,&mreq,sizeof(mreq)) ;

while(1){ 
    nbytes=recvfrom(fd,buf,bufsize,0,(struct sockaddr *) &addr,sizeof(addr));
    puts(buf); 
   }
 return 0; 
} 