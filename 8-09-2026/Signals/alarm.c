#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void handler(int sig) {
    printf("Timeout\n");
}

int main() {
    signal(SIGALRM, handler);
    alarm(5);
    pause();

    return 0;
}