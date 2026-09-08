#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main() {
    int p1[2], p2[2];
    char msg[100];

    pipe(p1);
    pipe(p2);

    if (fork() == 0) {
        close(p1[1]);
        close(p2[0]);

        read(p1[0], msg, sizeof(msg));
        printf("Child: %s\n", msg);

        strcpy(msg, "Hello Parent");
        write(p2[1], msg, strlen(msg) + 1);

        close(p1[0]);
        close(p2[1]);
    } else {
        close(p1[0]);
        close(p2[1]);

        strcpy(msg, "Hello Child");
        write(p1[1], msg, strlen(msg) + 1);

        read(p2[0], msg, sizeof(msg));
        printf("Parent: %s\n", msg);

        close(p1[1]);
        close(p2[0]);
    }

    return 0;
}