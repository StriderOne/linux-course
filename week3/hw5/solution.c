#define _GNU_SOURCE

#include <stdio.h> 
#include <unistd.h> 
#include <string.h>
#include <stdlib.h>

char* get_pid() {

    FILE * f = fopen("/proc/self/status", "r");
    char string [100];
    while ( fgets(string, 100, f) != NULL ) 
    {
        if (strcasestr(string, "Pid") != NULL)
        {
            char * pch = strtok (string,"\t ,.-"); 
            int c = 0;
            while (pch != NULL)                         
            {
                if (c > 0)  {
                    fclose(f);
                    // printf("1");
                    pch[strcspn(pch, "\n")] = 0;
                    return pch;
                }
                c += 1;
                pch = strtok (NULL, "\t ,.-");
            }
        }
    }
    fclose(f);
    return NULL;
}

int main() 
{
    printf("%s\n", get_pid());
    fclose(stdout);
    daemon(0, 0);
    // our process is now a daemon!
    sleep(600);
    return 0;
}