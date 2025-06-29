//iterative client handling
#include<sys/types.h> 
#include<sys/socket.h> 
#include<netinet/in.h> 
#include<sys/stat.h> 
#include<unistd.h> 
#include<stdlib.h> 
#include<stdio.h> 
#include<fcntl.h> 
#include <arpa/inet.h> 

 
void str_echo(int connfd) 
{ 
int n,bufsize = 1024; 
char *buffer = malloc(bufsize); 
again: while((n=recv(connfd, buffer, bufsize, 0))>0)  send(connfd,buffer,n,0); 
if(n<0)  goto again; 
free(buffer);
} 

int main() 
{ 
int create_socket, connfd, pid;
struct sockaddr_in address, cli_address;
socklen_t addrlen = sizeof(cli_address);
create_socket = socket(AF_INET, SOCK_STREAM, 0);
address.sin_family = AF_INET;
address.sin_addr.s_addr = INADDR_ANY;
address.sin_port = htons(15001);

bind(create_socket,(struct sockaddr *)&address, sizeof(address));

listen(create_socket, 3);
printf("Server is listening on port %d\n", ntohs(address.sin_port));

while (1) {
connfd = accept(create_socket, (struct sockaddr *)&cli_address, &addrlen);
printf("Client %s connected on port %d\n",inet_ntoa(cli_address.sin_addr), ntohs(cli_address.sin_port));
str_echo(connfd);
close(connfd);
printf("Client disconnected. Waiting for next client...\n");
}
return 0;
} 
/*
cc server.c -o server
./server 
*/