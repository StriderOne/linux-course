#define _GNU_SOURCE

#include <stdio.h> 
#include <unistd.h> 
#include <string.h>

#define BUF_SIZE 0x100

char* get_ppid(char* pid) {
    char parent_path[256];
    // printf("PID: %s\n", pid);
    sprintf(parent_path, "/proc/%s/status", pid);
    // printf("PARENT PATH: %s\n", parent_path);
    FILE * f = fopen(parent_path, "r");
    char string [100];
    while ( fgets(string, 100, f) != NULL ) 
    {
        if (strcasestr(string, "PPid") != NULL)
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

int main(int argc, char* argv[]) 
{
    printf("%s\n", argv[1]);
    char* ppid = get_ppid(argv[1]);
    while (strcmp(ppid, "1"))
    {   
        printf("%s", ppid);
        printf("\n");
        ppid = get_ppid(ppid);
    }
    printf("1");
    // printf("\n");
    return 0;
}