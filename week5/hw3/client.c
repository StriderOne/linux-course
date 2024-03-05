#include <stdio.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <string.h>


struct sockaddr_in local;

int client()
{
    int s = socket(AF_INET, SOCK_STREAM, 0);
    printf("socket = %d\n", s);

    inet_aton("127.0.0.1", &local.sin_addr);
    local.sin_port = htons(1234);
    local.sin_family = AF_INET;

    connect(s, (struct sockaddr*) &local, sizeof(local));;

    char buf[BUFSIZ]="12345\0";
    write(s, buf, strlen(buf)+1);
    char buf1[BUFSIZ];
    read(s, buf1, BUFSIZ);
    printf("%s", buf1);
    close(s);
}

int main() 
{
    client();
}