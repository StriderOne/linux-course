#include <stdio.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdlib.h>

struct sockaddr_in local;

int comp (const void * elem1, const void * elem2)
{
    char f = *((char*)elem1);
    char s = *((char*)elem2);
    if (f < s) return 1;
    if (f > s) return -1;
    return 0;
}

int server(int port) 
{
    int ss = socket (AF_INET, SOCK_STREAM, 0);
    int cs;

    inet_aton("127.0.0.1", &local.sin_addr);
    local.sin_port = htons(port);
    local.sin_family = AF_INET;

    bind(ss, (struct sockaddr*) &local, sizeof(local));
    listen(ss, 5);

    cs = accept(ss, NULL, NULL);

    char buf[BUFSIZ];
    while (1) 
    {
        read(cs, buf, BUFSIZ);
        if (strncmp(buf, "OFF", 3) == 0)
            break;
        qsort(buf, strlen(buf), 1, comp);

        write(cs, buf, strlen(buf)+1);
    }
    close(cs);
}

int main(int c, char **v)
{
    server(atoi(v[1]));
}