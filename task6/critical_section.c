#include <errno.h>
#include <fcntl.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "semaphores.h"

#define MAX_SLEEP_TIME 2

int main(int argc, char *argv[]) {
  if (argc != 2) {
    fprintf(stderr, "Użycie: %s <liczba_sekcji_krytycznych>\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  int section_number = atoi(argv[1]);
  int id = getpid();
  srand(time(NULL));

  sem_t *sem = open_semaphore(SEM_NAME);
  if (!sem) exit(EXIT_FAILURE);

  for (int i = 0; i < section_number; i++) {
    printf("Proces %d: Oczekiwanie na wejście do sekcji krytycznej %d\n", id, i + 1);
    if (!wait_semaphore(sem)) exit(EXIT_FAILURE);

    printf("Proces %d: Wchodzenie do sekcji krytycznej %d\n", id, i + 1);

    int fd = open(FILE_NAME, O_RDWR);
    if (fd == -1) {
      perror("open");
      exit(EXIT_FAILURE);
    }

    int number;
    char buffer[10];
    if (read(fd, buffer, sizeof(buffer)) == -1) {
      perror("read");
      close(fd);
      exit(EXIT_FAILURE);
    }

    number = atoi(buffer);
    number += 1;

    lseek(fd, 0, SEEK_SET);
    if (dprintf(fd, "%d\n", number) < 0) {
      perror("dprintf");
      close(fd);
      exit(EXIT_FAILURE);
    }

    close(fd);

    printf("Proces %d: Opuszcza sekcje krytyczną %d, z wartością %d\n", id, i + 1, number);

    if (!post_semaphore(sem)) exit(EXIT_FAILURE);

    sleep(rand() % MAX_SLEEP_TIME);
  }

  if (!close_semaphore(sem)) exit(EXIT_FAILURE);

  return 0;
}