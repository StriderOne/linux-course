#include <stdio.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <string.h>

struct sockaddr_in local;

int main(int c, char **v) 
{
    int flag = 1;
    int host = atoi(v[1]);
    int s = socket(AF_INET, SOCK_DGRAM, 0);
    // printf("socket = %d\n", s);

    inet_aton("127.0.0.1", &local.sin_addr);
    local.sin_port = htons(host);
    local.sin_family = AF_INET;

    int result = bind(s, (struct sockaddr*) &local, sizeof(local));
    // printf("%d\n", result);

    char buf[BUFSIZ];
    while (flag)
    {
        int i = 0;
        for(i=0; i < BUFSIZ; i++) buf[i] = 0;
        read(s, buf, BUFSIZ);
        
        // buf[strcspn(buf, "\n")] = 0;
        // printf("%d", strcmp(buf, "OFF"));
        if (strncmp(buf, "OFF", 3) == 0)
            break;
        printf("%s\n", buf);
    }
    
}