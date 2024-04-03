#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  for (int i = 0; i < 3; i++) {
    printf("Iteracja numer: %d\n", i + 1);
    pid_t pid = fork();

    switch (pid) {
      case -1:
        perror("fork");
        exit(EXIT_FAILURE);
        break;
      case 0:
        execlp(argv[1], argv[1], (char *)NULL);
        perror("execlp error");
        _exit(2);
        break;
      default:
        wait(NULL);
        break;
    }
  }

  return 0;
}