#include <stdio.h>
#include <unistd.h>

int main() {
    int p[2], n, sum = 0;
    pipe(p);

    if (fork() == 0) {
        close(p[1]);
        while (read(p[0], &n, sizeof(n)) > 0)
            sum += n;
        printf("Sum: %d\n", sum);
        close(p[0]);
    } else {
        close(p[0]);
        for (n = 1; n <= 5; n++)
            write(p[1], &n, sizeof(n));
        close(p[1]);
    }

    return 0;
}