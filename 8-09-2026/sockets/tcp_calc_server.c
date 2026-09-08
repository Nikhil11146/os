#include <stdio.h>
#include <unistd.h>
#include <arpa/inet.h>

struct data {
    float a, b, result;
    char op;
};

int main() {
    int s = socket(AF_INET, SOCK_STREAM, 0), c;
    struct data d;
    struct sockaddr_in a = {0};

    a.sin_family = AF_INET;
    a.sin_port = htons(8080);
    a.sin_addr.s_addr = INADDR_ANY;

    bind(s, (struct sockaddr *)&a, sizeof(a));
    listen(s, 1);
    c = accept(s, NULL, NULL);

    read(c, &d, sizeof(d));

    if (d.op == '+') d.result = d.a + d.b;
    else if (d.op == '-') d.result = d.a - d.b;
    else if (d.op == '*') d.result = d.a * d.b;
    else if (d.op == '/') d.result = d.a / d.b;

    write(c, &d.result, sizeof(d.result));

    close(c);
    close(s);
    return 0;
}