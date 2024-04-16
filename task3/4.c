#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

// Program wywołuje 3 razy funkcję `fork` która wywołuje pierwszy program poprzez `execlp`.

int main() {
  pid_t child_pid;
  int err;
  for (int i = 0; i < 3; i++) {
    child_pid = fork();

    switch (child_pid) {
      case -1:
        perror("fork");
        exit(EXIT_FAILURE);
      case 0:
        err = execlp("output/1", "output/1", NULL);
        if (err == -1) {
          perror("execlp");
          exit(EXIT_FAILURE);
        }

      default:
        break;
    }
  }
  exit(EXIT_SUCCESS);
}
