#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>

int main() {
    int s = socket(AF_INET, SOCK_STREAM, 0);
    int c;
    char msg[100];
    struct sockaddr_in a = {0};

    a.sin_family = AF_INET;
    a.sin_port = htons(8080);
    a.sin_addr.s_addr = INADDR_ANY;

    bind(s, (struct sockaddr *)&a, sizeof(a));
    listen(s, 1);

    c = accept(s, NULL, NULL);
    read(c, msg, sizeof(msg));
    printf("Client: %s\n", msg);

    close(c);
    close(s);
    return 0;
}