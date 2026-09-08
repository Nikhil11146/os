#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>

int main() {
    int s = socket(AF_INET, SOCK_DGRAM, 0);
    char msg[] = "Hello Server";
    struct sockaddr_in a = {0};

    a.sin_family = AF_INET;
    a.sin_port = htons(8080);
    inet_pton(AF_INET, "127.0.0.1", &a.sin_addr);

    sendto(s, msg, strlen(msg) + 1, 0, (struct sockaddr *)&a, sizeof(a));

    close(s);
    return 0;
}