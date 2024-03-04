#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>

#define SHMSZ  1000

int main(int argc, char* argv[])
{
    int shmid, shmid_1, shmid_2;
    key_t key_1, key_2;
    int *array_1;
    int *array_2;
    int *array;

    key_1 = atoi(argv[1]);
    key_2 = atoi(argv[2]);

    /*
     * Locate the segment.
     */
    if ((shmid_1 = shmget(key_1, SHMSZ, 0666)) < 0) {
        perror("shmget");
        exit(1);
    }
    if ((shmid_2 = shmget(key_2, SHMSZ, 0666)) < 0) {
        perror("shmget");
        exit(1);
    }

    /*
     * Now we attach the segment to our data space.
     */
    if ((array_1 = (int *) shmat(shmid_1, NULL, 0)) == (int *) -1) {
        perror("shmat");
        exit(1);
    }
    if ((array_2 = (int *) shmat(shmid_2, NULL, 0)) == (int *) -1) {
        perror("shmat");
        exit(1);
    }

    key_t key;

    key = 5678;

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

    int i = 0;
    for (i = 0; i < 100; i++)
        array[i] = array_1[i] + array_2[i];

    printf("%d\n", key);

    exit(0);
}
