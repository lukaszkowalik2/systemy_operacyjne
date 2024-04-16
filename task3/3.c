#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

// Program w procesie macierzystym tworzy proces potomny poprzez funckje `fork` i sprawia aby stał się on lidreme grupy a następnie wywołuje funckje execlp która uruchamia program 4.c. Następnie z pierwszego procesu macierzystego wysyła sygnały do całej grupy procesów protomych po uprzednim sprawdzeniu czy istnieją. Proces będący liderem grupy procesów ignoruje sygnały a ana końcu czeka na zakońćzenie wzystkich swoich pocesów potomnych.

typedef void (*sighandler_t)(int);

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
      pid_t setpgid_pid = setpgid(0, 0);
      if (setpgid_pid < 0) {
        perror("setpgid");
        exit(EXIT_FAILURE);
      }
      sighandler_t stp = signal(SIGTSTP, SIG_IGN);  // Ctrl+Z
      if (stp == SIG_ERR) {
        perror("signal");
        exit(EXIT_FAILURE);
      }
      int err = execlp(argv[1], argv[1], (char *)NULL);
      if (err == -1) {
        perror("execlp");
        exit(EXIT_FAILURE);
      }
      break;
    }

    default: {
      sleep(3.5);
      pid_t pgid = getpgid(pid);
      if (pgid < 0) {
        perror("getpgid");
        exit(EXIT_FAILURE);
      }
      pid_t setpgid_pid = kill(-pgid, 0);
      if (setpgid_pid == 0) {
        printf("Wysłano sygnał do grupy procesów potomnych\n");
        sleep(1);
        kill(-pgid, SIGQUIT);
      } else {
        printf("Grupa procesów potomnych nie istnieje\n");
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

      exit(EXIT_SUCCESS);
      break;
    }
  }

  exit(EXIT_SUCCESS);
}
