#define _GNU_SOURCE

#include <stdio.h> 
#include <unistd.h> 
#include <string.h>

#define BUF_SIZE 0x100

int main() 
{
    char buf[BUF_SIZE];
    int len, i;
    FILE * f;
    f = fopen("/proc/self/status", "r");
    char mystring [100];

    // printf("%d\n", getppid());

    while ( fgets(mystring, 100, f) != NULL ) {// считать символы из файла
        
        if (strcasestr(mystring, "PPid") == NULL)
            continue;
        char * pch = strtok (mystring,"\t ,.-"); 
        int c = 0;
        while (pch != NULL)                         
        {
            if (c > 0) {
                printf("%s", pch);
                break;
            }
            c += 1;
            pch = strtok (NULL, "\t ,.-");
        }
        if (c > 0)
            break;
        
    }
    fclose(f);
    return 0;
}