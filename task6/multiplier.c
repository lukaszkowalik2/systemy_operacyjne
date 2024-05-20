#include <fcntl.h>
#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

#include "./include/semaphores.h"

void cleanup() {
  unlink_semaphore();
}

void handle_sigint(int sig) {
  cleanup();
  exit(EXIT_FAILURE);
}

int main(int argc, char *argv[]) {
  if (argc != 4) {
    fprintf(stderr, "Użycie: %s <liczba_procesów> <liczba_sekcji_krytycznych>\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  char *program_path = argv[1];
  int num_processes = atoi(argv[2]);
  int num_sections = atoi(argv[3]);

  signal(SIGINT, handle_sigint);
  atexit(cleanup);

  sem_t *sem = create_semaphore(1);
  if (!sem) exit(EXIT_FAILURE);

  int fd = open(FILE_NAME, O_CREAT | O_WRONLY | O_TRUNC, 0644);
  if (fd == -1) {
    perror("open");
    exit(EXIT_FAILURE);
  }

  close(fd);

  for (int i = 0; i < num_processes; i++) {
    pid_t pid = fork();
    switch (pid) {
      case -1: {
        perror("fork multi");
        break;
      }
      case 0: {
        int status = execlp(program_path, program_path, argv[3], NULL);
        if (status == -1) {
          perror("execlp");
          exit(EXIT_FAILURE);
        }
        break;
      }
      default: {
        wait(NULL);
        break;
      }
    }
  }

  FILE *file = fopen(FILE_NAME, "r");
  if (file == NULL) {
    perror("fopen");
    exit(EXIT_FAILURE);
  }

  int final_value;
  if (fscanf(file, "%d", &final_value) != 1) {
    perror("fscanf");
    fclose(file);
    exit(EXIT_FAILURE);
  }

  printf("Finalna wartość %s: %d\n", FILE_NAME, final_value);
  printf("Wartość %s jest %s\n", FILE_NAME, (final_value == num_processes * num_sections) ? "poprawna" : "niepoprawna");

  fclose(file);
  exit(EXIT_SUCCESS);
}
