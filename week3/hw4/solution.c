#define _GNU_SOURCE

#include <stdio.h> 
#include <unistd.h> 
#include <string.h>
#include <stdlib.h>


#define BUF_SIZE 0x100

void get_childrens_pid(char* pid, int* counter) {
    char childrens[256];

    // printf("Current pid: %s", pid);
    sprintf(childrens, "/proc/%s/task/%s/children", pid, pid);
    // printf("PARENT PATH: %s\n", childrens);
    FILE * f = fopen(childrens, "r");
    char string [1000];
    if (f == NULL)
        return;
 
    fgets(string, 256, f);
    fclose(f);
    char* token;
    char* rest = string;

    while ((token = strtok_r(rest, " ", &rest)))                         
    {
       
        if (isdigit(token[0])) {
            // printf("%s \n", token);
            (*counter)++;
            get_childrens_pid(token, counter);
        }
       
    }
 
    return;
}

int main(int argc, char* argv[]) 
{
    int counter = 0;
    get_childrens_pid(argv[1], &counter);
    printf("%d", counter+1);
    return 0;
}