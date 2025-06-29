#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<arpa/inet.h>
#include<string.h>

void str_echo(int sockfd) {
    int bufsize = 1024, n;
    char *buffer = malloc(bufsize);
    struct sockaddr_in cli_address;
    socklen_t addrlen = sizeof(cli_address);

    while (1) {
        n = recvfrom(sockfd, buffer, bufsize, 0, (struct sockaddr*)&cli_address, &addrlen);
        sendto(sockfd, buffer, n, 0, (struct sockaddr*)&cli_address, addrlen);
    }
    free(buffer);
}

int main() {
    int sockfd;
    struct sockaddr_in addr;

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    printf("The socket was created\n");

    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(16001);

    if (bind(sockfd, (struct sockaddr*)&addr, sizeof(addr)) == 0) printf("Binding Socket\n");

    str_echo(sockfd);
    close(sockfd);
    return 0;
}
/*
cc server.c -o server
./server 
*/
