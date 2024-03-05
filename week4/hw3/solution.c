#include <signal.h>
#include <stdio.h>
#include <unistd.h>

int counter_1 = 0, counter_2 = 0;
int flag = 0;

void sigusr1_handler(int signalno)
{
    counter_1++;
}

void sigusr2_handler(int signalno)
{
    counter_2++;
}

void signal_term(int signalno)
{
    flag = 1;
}

int main()
{
    // printf("%d \n", getpid());
    signal(SIGUSR1, sigusr1_handler);
    signal(SIGUSR2, sigusr2_handler);
    signal(SIGTERM, signal_term);
    
    while (1) 
    {
        if (flag == 1)
            break;
    }
    printf("%d %d\n", counter_1, counter_2);

    return 0;
}