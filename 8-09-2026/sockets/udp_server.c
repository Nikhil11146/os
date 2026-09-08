#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>

int main() {
    int s = socket(AF_INET, SOCK_DGRAM, 0);
    char msg[100];
    struct sockaddr_in a = {0};
    socklen_t len = sizeof(a);

    a.sin_family = AF_INET;
    a.sin_port = htons(8080);
    a.sin_addr.s_addr = INADDR_ANY;

    bind(s, (struct sockaddr *)&a, sizeof(a));

    recvfrom(s, msg, sizeof(msg), 0, (struct sockaddr *)&a, &len);
    printf("Client: %s\n", msg);

    close(s);
    return 0;
}