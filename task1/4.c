/*
  Program ten korzyssta z funkcji fork, która jest wywoływana w trzy razy w funkcji for w celu utworzenia procesów potomnych. Następnie dla każdego oraz dla procesu macierzystego wypisuje identyfikatory UID, GID, PID, PPID i PGID. Została użyta funkcja `sleep`. Funkcja `sleep` jest umieszczona w miejscach, aby pokolenia pojawiały się grupowane pokoleniami na ekranie. Wyniki programu oraz drzewo genealogiczne stworzone z wyników programu zostały zapisane w pliku `process_tree.txt`.
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
  printf("UID: %d, GID: %d, PID: %d, PPID: %d, PGID: %d\n", getuid(), getgid(), getpid(), getppid(), getpgid(0));
}

int main() {
  printf("Parent process:    ");
  print_process_info();

  for (int i = 0; i < 3; ++i) {
    pid_t pid = fork();

    switch (pid) {
      case -1:
        perror("fork failed");
        exit(EXIT_FAILURE);
        break;
      case 0:
        printf("Child process %d:    ", i + 1);
        print_process_info();
        sleep(0.5);
        break;
      default:
        wait(NULL);
        break;
    }
  }

  sleep(2);

  return 0;
}