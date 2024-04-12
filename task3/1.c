#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// Program ma na celu i wykonanie operacji domyślnej przy kliknięciu Ctrl + \, zignorowanie sygnału przy kliknięciu Ctrl+C oraz wykonanie własnej akcji przy kliknięciu Ctrl+Z.

typedef void (*sighandler_t)(int);

void custom_handler() {
  printf("\n Moja akcja\n");

  int pid = getpid();
  int gid = getgid();
  int uid = getuid();
  int ppid = getppid();
  int pgid = getpgid(0);

  printf("UID: %d, GID: %d, PID: %d, PPID: %d, PGID: %d\n", uid, gid, pid, ppid, pgid);
}

int main() {
  sighandler_t stp = signal(SIGTSTP, custom_handler);  // Ctrl+Z
  sighandler_t sigint = signal(SIGINT, SIG_IGN);       // Ctrl+C
  sighandler_t quit = signal(SIGQUIT, SIG_DFL);        // Ctrl+\/

  if (stp == SIG_ERR || sigint == SIG_ERR || quit == SIG_ERR) {
    perror("signal");
    exit(EXIT_FAILURE);
  }

  printf("PID: %d\n", getpid());
  printf("Oczekiwanie na sygnały...\n");

  pause();

  exit(EXIT_SUCCESS);
}
