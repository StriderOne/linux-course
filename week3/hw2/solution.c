#include <dirent.h>
#include <stdio.h> 
#include <unistd.h> 
#include <string.h>
#include <stdlib.h>


int main(void)
{
    struct dirent **namelist;
    FILE * f;
    int n;
    char buffer[270];
    char mystring [100];
    int count = 0;
    n = scandir("/proc/", &namelist, NULL, alphasort);
    if (n < 0)
        perror("scandir");
        // return 1;
    
    while (n--) {
        if (isdigit(namelist[n]->d_name[0]) == 0)
            continue;

        sprintf(buffer, "/proc/%s/comm", namelist[n]->d_name);
        free(namelist[n]);
        
        char name[256];
        f = fopen(buffer, "r");
        if (f == NULL)
            continue;
        fscanf(f, "%s\n", name);

        if (strcmp(name, "genenv") == 0) 
            count++;
        
        fclose(f);
    }
    
    free(namelist);
    printf("%d\n", count);

    return 0;
}