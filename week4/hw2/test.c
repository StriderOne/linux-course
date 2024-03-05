#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main() 
{
    int f1 = open("./in1", O_RDWR);
    int f2 = open("./in2", O_RDWR);
    
    write(f1, "12", 100);
    sleep(5);
    write(f2, "100", 100);
    sleep(5);
    write(f1, "1", 100);
    sleep(5);
    write(f2, "12", 100);
    sleep(5);


    close(f1);
    close(f2);

    return 0;
}