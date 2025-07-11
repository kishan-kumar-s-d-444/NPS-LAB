#include<sys/types.h> 
#include<sys/socket.h> 
#include<netinet/in.h> 
#include<sys/stat.h> 
#include<unistd.h> 
#include<stdlib.h> 
#include<stdio.h> 
#include<fcntl.h> 
#include <arpa/inet.h> 

int main(int argc,char *argv[]) 
{ 
int create_socket, cont; 
char *buffer = malloc(1024),fname[256]; 
struct sockaddr_in address; 

if ((create_socket = socket(AF_INET,SOCK_STREAM,0)) > 0)  printf("The Socket was created\n"); 

address.sin_family = AF_INET; 
address.sin_port = htons(15001); 
inet_pton(AF_INET,argv[1],&address.sin_addr); 
if (connect(create_socket,(struct sockaddr *) &address, sizeof(address)) == 0)  printf("The connection was accepted with the server %s...\n",argv[1]); 

printf("Enter The Filename to Request : "); scanf("%s",fname); 
send(create_socket, fname, sizeof(fname), 0); 
printf("Request Accepted... Receiving File...\n\n"); 
printf("The contents of file are...\n\n"); 

while((cont=recv(create_socket, buffer, 1024, 0))>0) write(1, buffer, cont); 
printf("\nEOF\n"); 
return close(create_socket); 
}

/*
run server first
cc client.c -o client
./client 127.0.0.1
*/