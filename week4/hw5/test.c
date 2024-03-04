#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>

#define SHMSZ     27

int main(int argc, char* argv[])
{
    char c;
    int shmid;
    key_t key;
    char *shm, *s;
    int *array;

    /*
     * We'll name our shared memory segment
     * "5678".
     */
    key = atoi(argv[1]);

    /*
     * Create the segment.
     */
    if ((shmid = shmget(key, SHMSZ, IPC_CREAT | 0666)) < 0) {
        perror("shmget");
        exit(1);
    }

    /*
     * Now we attach the segment to our data space.
     */
    if ((array = (int *) shmat(shmid, NULL, 0)) == (int *) -1) {
        perror("shmat");
        exit(1);
    }

    for (int i = 0; i < 200; i++)
        array[i] = i;
    // *s = NULL

    exit(0);
}
