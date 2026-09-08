#include <stdio.h>
#include <unistd.h>
#include <arpa/inet.h>

struct data {
    float a, b;
    char op;
};

int main() {
    int s = socket(AF_INET, SOCK_STREAM, 0);
    float result;
    struct data d;
    struct sockaddr_in a = {0};

    a.sin_family = AF_INET;
    a.sin_port = htons(8080);
    inet_pton(AF_INET, "127.0.0.1", &a.sin_addr);

    connect(s, (struct sockaddr *)&a, sizeof(a));

    scanf("%f %c %f", &d.a, &d.op, &d.b);
    write(s, &d, sizeof(d));
    read(s, &result, sizeof(result));

    printf("Result: %.2f\n", result);

    close(s);
    return 0;
}