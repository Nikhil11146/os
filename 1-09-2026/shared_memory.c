#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <unistd.h>

#define SHM_SIZE 1024

int main() {

    key_t key;
    int shmid;
    pid_t pid;

    char *shared_memory;

    key = ftok(".", 'B');

    if (key == -1) {
        perror("ftok");
        exit(1);
    }

    shmid = shmget(key, SHM_SIZE, 0666 | IPC_CREAT);

    if (shmid == -1) {
        perror("shmget");
        exit(1);
    }

    shared_memory = (char *)shmat(shmid, NULL, 0);

    if (shared_memory == (char *)-1) {
        perror("shmat");
        exit(1);
    }

    pid = fork();

    if (pid < 0) {
        perror("fork");
        exit(1);
    }

    if (pid > 0) {

        printf("Process 1: Writing data to shared memory...\n");
        strcpy(shared_memory, "Hello from Process 1");
        wait(NULL);

        if (shmdt(shared_memory) == -1) {
            perror("shmdt");
            exit(1);
        }

        if (shmctl(shmid, IPC_RMID, NULL) == -1) {
            perror("shmctl");
            exit(1);
        }
    } else {
        sleep(1);

        printf("Process 2: Reading data from shared memory...\n");

        printf("\nProcess 2 received:\n");
        printf("%s\n", shared_memory);

        if (shmdt(shared_memory) == -1) {
            perror("shmdt");
            exit(1);
        }
    }

    return 0;
}