

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

// Program uruchamia program 1.c poprzez funckje execlp w procesie potomnym innego procesu stworzonego poprzez funckje `fork`. Wysyła on do tego procesu sygnał SIGQUIT.

int main(int argc, char *argv[]) {
  pid_t pid;
  int status;

  pid = fork();

  switch (pid) {
    case -1: {
      perror("fork");
      exit(EXIT_FAILURE);
      break;
    }
    case 0: {
      int err = execlp(argv[1], argv[1], (char *)NULL);
      if (err == -1) {
        perror("execlp");
        exit(EXIT_FAILURE);
      }
      printf("Proces potomny PID: %d\n", getpid());
      break;
    }

    default: {
      printf("Proces macierzysty PID: %d\n", getpid());
      int child_status = kill(pid, 0);
      if (child_status == 0) {
        printf("Proces potomny PID: %d\n", pid);
        sleep(1);
        kill(pid, SIGQUIT);  // Ctrl+\/
      } else {
        printf("Proces potomny nie istnieje\n");
      }

      if (wait(&status) == -1) {
        perror("wait");
        exit(EXIT_FAILURE);
      }
      if (WIFEXITED(status)) {
        printf("Status zakończenia: %d\n", WEXITSTATUS(status));
      }
      if (WIFSIGNALED(status)) {
        printf("Proces potomny zakończony przez sygnał: %d (%s)\n", WTERMSIG(status), strsignal(WTERMSIG(status)));
      }

      break;
    }
  }

  exit(EXIT_SUCCESS);
}
