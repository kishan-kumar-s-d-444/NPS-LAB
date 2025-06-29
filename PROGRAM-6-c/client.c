#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<arpa/inet.h>
#include<string.h>

void str_cli(FILE *fp, int sockfd, struct sockaddr *serv_address, int servlen) {
    int bufsize = 1024, cont;
    char *buffer = malloc(bufsize);
    struct sockaddr_in addr;

    while (fgets(buffer, bufsize, fp) != NULL) {
        sendto(sockfd, buffer, bufsize, 0, serv_address, servlen);
        cont = recvfrom(sockfd, buffer, bufsize, 0, (struct sockaddr*)&addr,sizeof(addr));
        if (cont > 0) {
            printf("Reply from %s: ", inet_ntoa(addr.sin_addr));
            fputs(buffer, stdout);
        }
    }
    printf("\nEOF\n");
    free(buffer);
}

int main(int argc, char *argv[]) {
    int sockfd;
    struct sockaddr_in addr;
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    addr.sin_family = AF_INET;
    addr.sin_port = htons(16001);
    inet_pton(AF_INET, argv[1], &addr.sin_addr);

    str_cli(stdin, sockfd, (struct sockaddr*)&addr, sizeof(addr));
    close(sockfd);
    return 0;
}

/*
run server first
cc client.c -o client
./client 127.0.0.1
*/