#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

// Program implementuje problem "Producenta i konsumenta" przy użyciu potoków nienazwanych. Producent pobiera surowiec z pliku tekstowego za pomocą funkcji `read`, a konsument pobiera surowiec z potoku również za pomocą funkcji `read` i zapisuje go do pliku tekstowego za pomocą funkcji `write`. Dodatkowo, program symuluje różną szybkość działania za pomocą funkcji `sleep`. Po wykonaniu akcji program zamyka potok oraz otwarte pliki. Po zakończeniu programu oba pliki tekstowe powinny być identyczne, co jest sprawdzane za pomocą polecenia `diff -s`.

#define BUF_SIZE 64
#define MAX_SLEEP_TIME 2

void read_from_pipe(int filedes, char *filename);
void write_to_pipe(int filedes, char *filename);

int main(int argc, char *argv[]) {
  srand(time(NULL));
  if (argc != 3) {
    fprintf(stderr, "Użycie: %s <input_file> <output_file>\n", argv[0]);
    exit(EXIT_FAILURE);
  }
  int filedes[2];
  if (pipe(filedes) == -1) {
    perror("pipe");
    exit(EXIT_FAILURE);
  }

  int pid = fork();

  switch (pid) {
    case -1: {
      perror("fork");
      exit(EXIT_FAILURE);
      break;
    }
    case 0: {
      // proces potomny
      close(filedes[0]);
      write_to_pipe(filedes[1], argv[1]);
      close(filedes[1]);
      wait(NULL);
      break;
    }
    default: {
      // proces macierzysty
      close(filedes[1]);
      read_from_pipe(filedes[0], argv[2]);
      close(filedes[0]);
      break;
    }
  }
  exit(EXIT_SUCCESS);
}

void write_to_pipe(int filedes, char *filename) {
  char buf[BUF_SIZE];
  size_t bytes_read;

  int read_file = open(filename, O_RDONLY);
  if (read_file == -1) {
    perror("open read_file");
    exit(EXIT_FAILURE);
  }

  while ((bytes_read = read(read_file, buf, sizeof(buf))) > 0) {
    ssize_t bytes_written = write(filedes, buf, bytes_read);
    printf("Wysłano do potoku: %s\n", buf);
    if (bytes_written == -1) {
      perror("write input_file\n");
      close(read_file);
      close(filedes);
      exit(EXIT_FAILURE);
    }
    sleep(rand() % MAX_SLEEP_TIME);
  }
  close(read_file);
}

void read_from_pipe(int filedes, char *filename) {
  char buf[BUF_SIZE];
  size_t bytes_read;

  int output_file = open(filename, O_WRONLY | O_TRUNC);
  if (output_file == -1) {
    perror("open output_file");
    exit(EXIT_FAILURE);
  }
  while ((bytes_read = read(filedes, buf, sizeof(buf))) > 0) {
    ssize_t bytes_written = write(output_file, buf, sizeof(buf));
    printf("Odczytano z potoku: %s\n", buf);
    if (bytes_written == -1) {
      perror("write output_file\n");
      close(output_file);
      close(filedes);
      exit(EXIT_FAILURE);
    }
    sleep(rand() % MAX_SLEEP_TIME);
  }
  close(output_file);
}