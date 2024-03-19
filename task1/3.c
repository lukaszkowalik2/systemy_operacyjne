#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    for (int i = 0; i < 3; i++) {
        printf("Iteracja numer: %d\n", i + 1);
        pid_t pid = fork();

        switch (pid) {
            case -1:
                perror("fork");
                exit(EXIT_FAILURE);
                break;
            case 0:
                printf("UID: %d\n", getuid());
                printf("GID: %d\n", getgid());
                printf("PID: %d\n", getpid());
                printf("PPID: %d\n", getppid());
                printf("PGID: %d\n", getpgid(0));
                exit(EXIT_SUCCESS);
                break;
            default:
                int status;
                wait(&status);
                break;
        }
    }

    return 0;
}