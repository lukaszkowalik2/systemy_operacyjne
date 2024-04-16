#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  const char fifo_path[16] = "./output/myfifo";
  int err = mkfifo(fifo_path, 0666);
  if (err == -1) {
    perror("mkfifo");
    exit(EXIT_FAILURE);
  }

  if (argv[1] || !argv[2]) {
    printf("Aby użyć tego programu musisz podać poprawnie argumenty %s <nazwa_pliku_wejścia> <nazwa_pliku_wyjścia>", argv[0]);
  }

  pid_t pid;
  pid = fork();

  switch (pid) {
    case -1: {
      perror("fork");
      exit(EXIT_FAILURE);
    }
    case 0: {
      printf("parent");
    }
    default: {
      printf("poto");
    }
  }

  // rmfifo(fifo_path);
  exit(EXIT_SUCCESS);
}