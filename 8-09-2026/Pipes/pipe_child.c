#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main() {
    int p[2];
    char msg[100];

    pipe(p);

    if (fork() == 0) {
        close(p[1]);
        read(p[0], msg, sizeof(msg));
        printf("Child: %s\n", msg);
        close(p[0]);
    } else {
        close(p[0]);
        strcpy(msg, "Hello Child");
        write(p[1], msg, strlen(msg) + 1);
        close(p[1]);
    }

    return 0;
}