#include<sys/types.h> 
#include<sys/socket.h> 
#include<netinet/in.h> 
#include<sys/stat.h> 
#include<unistd.h> 
#include<stdlib.h> 
#include<stdio.h> 
#include<fcntl.h> 
#include <arpa/inet.h> 
#include<string.h> 


void str_echo(int connfd) 
{ 
int n, bufsize = 10240; 
char *buffer = malloc(bufsize); 

while((n=recv(connfd, buffer, bufsize, 0))>0) { 
     fputs("client:",stdout); 
     fputs(buffer,stdout); 
     fputs("Me:",stdout); 
     if(fgets(buffer,bufsize,stdin)!=NULL) send(connfd, buffer, bufsize, 0);
     bzero(buffer,bufsize); 
    }
} 

int main() {
    int create_socket, connfd;
    struct sockaddr_in address, cli_address;
    socklen_t addrlen = sizeof(cli_address);

    create_socket = socket(AF_INET, SOCK_STREAM, 0);
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(16001);
    bind(create_socket, (struct sockaddr *)&address, sizeof(address));
    listen(create_socket, 3);

    while (1) {
        connfd = accept(create_socket, (struct sockaddr *)&cli_address, &addrlen);
        printf("Client %s connected on port %d\n",inet_ntoa(cli_address.sin_addr), ntohs(cli_address.sin_port));
        if (fork() == 0) {
            close(create_socket);
            str_echo(connfd);
            close(connfd);
            // exit(0);
        }
        close(connfd);
    }
    return 0;
}
/*
cc server.c -o server
./server 
*/