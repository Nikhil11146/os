#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/wait.h>
#include <unistd.h>

struct message {
    long msg_type;
    int student_id;
    char name[50];
    float marks;
};

int main() {
    key_t key;
    int msgid;
    pid_t pid;

    struct message msg;

    key = ftok(".", 'A');

    if (key == -1) {
        perror("ftok");
        exit(1);
    }

    msgid = msgget(key, 0666 | IPC_CREAT);

    if (msgid == -1) {
        perror("msgget");
        exit(1);
    }

    pid = fork();

    if (pid < 0) {
        perror("fork");
        exit(1);
    }

    if (pid > 0) {

        printf("Enter Student ID: ");
        scanf("%d", &msg.student_id);

        printf("Enter Student Name: ");
        scanf("%49s", msg.name);

        printf("Enter Marks: ");
        scanf("%f", &msg.marks);

        msg.msg_type = 1;

        if (msgsnd(msgid, &msg, sizeof(msg) - sizeof(long), 0) == -1) {
            perror("msgsnd");
            exit(1);
        }

        printf("\nSender: Student information sent successfully.\n");

        wait(NULL);

        if (msgctl(msgid, IPC_RMID, NULL) == -1) {
            perror("msgctl");
            exit(1);
        }
    }

    else {
        if (msgrcv(msgid, &msg, sizeof(msg) - sizeof(long), 1, 0) == -1) {
            perror("msgrcv");
            exit(1);
        }

        printf("\nReceiver:\n");
        printf("Student ID: %d\n", msg.student_id);
        printf("Name      : %s\n", msg.name);
        printf("Marks     : %.2f\n", msg.marks);
    }

    return 0;
}