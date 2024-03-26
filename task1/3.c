/*
  Program ten korzyssta z funkcji fork, która jest wywoływana w trzy razy w funkcji for w celu utworzenia procesów potomnych. Następnie dla każdego oraz dla procesu macierzystego wypisuje identyfikatory UID, GID, PID, PPID i PGID. Została użyta funkcja `sleep`.
  ----------------------------------------------------------------------
  Autor: Łukasz Kowalik
  ----------------------------------------------------------------------
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

void print_process_info() {
  int pid = getpid();
  int gid = getgid();
  int uid = getuid();
  int ppid = getppid();
  int pgid = getpgid(0);

  printf("UID: %d, GID: %d, PID: %d, PPID: %d, PGID: %d\n", uid, gid, pid, ppid, pgid);
}

int main() {
  printf("Parent process:    ");
  print_process_info();
  for (int i = 0; i < 3; i++) {
    pid_t pid = fork();

    switch (pid) {
      case -1:
        perror("fork failed");
        exit(EXIT_FAILURE);
        break;
      case 0:
        printf("Child process %d:    ", i + 1);
        print_process_info();
        break;
      default:
        sleep(1);
        break;
    }
  }
  sleep(4);

  return 0;
}