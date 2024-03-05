#include <stdio.h>
#include <unistd.h>
#include <sys/select.h>
#include <fcntl.h>
#include <stdbool.h>

int read_and_report(int fd, int* counter) {
    char buf[100];

    // printf("FD %d is ready to read\n", fd);

    int bytes = read(fd, buf, 100);
    if (bytes <= 0)
        return 1;
    buf[bytes] = 0;
    int value = atoi(buf);
    // printf("Get %d bytes from %d : %d\n", bytes, fd, value);
    (*counter) += value;
    return 0;
}

int main() {
    int f1 = open("./in1", O_RDONLY);
    int f2 = open("./in2", O_RDONLY);

    if (! (f1 && f2)) {
        printf("Error with opening pipes \n");
        return 0;
    }

    // printf("Descriptors: %d %d\n", f1, f2);

    fd_set read_set;
    int counter = 0;
    while (true)
    {
        FD_ZERO(&read_set);
        FD_SET(f1, &read_set);
        FD_SET(f2, &read_set);
        int res1 = 0, res2 = 0;
        int result = select(f2+1, &read_set, NULL, NULL, NULL);
        if(result)
        {
            if( FD_ISSET(f1, &read_set) )
                res1 = read_and_report(f1, &counter);
            if( FD_ISSET(f2, &read_set) )
                res2 = read_and_report(f2, &counter);
            if (res1 == 1 || res2 == 1)
                break;
        }
        
        
    }
    printf("%d\n", counter);
    close(f1);
    close(f2);

    return 0;
}