#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void handler(int sig) {
    printf("Child received signal\n");
}

int main() {
    int pid = fork();

    if (pid == 0) {
        signal(SIGUSR1, handler);
        pause();
    } else {
        sleep(1);
        kill(pid, SIGUSR1);
    }

    return 0;
}