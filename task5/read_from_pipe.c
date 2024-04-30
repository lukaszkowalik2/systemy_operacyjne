#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

#define BUF_SIZE 64
#define MAX_SLEEP_TIME 2

int main(int argc, char *argv[]) {
  if (argc != 3) {
    printf("Użycie: %s <write_file> <fifo_path>\n", argv[0]);
    exit(EXIT_FAILURE);
  }
  char buf[BUF_SIZE];
  size_t bytes_read;

  int output_file = open(argv[1], O_WRONLY | O_TRUNC);
  if (output_file == -1) {
    perror("open output_file");
    exit(EXIT_FAILURE);
  }

  int fifo = open(argv[2], O_RDONLY);
  if (fifo == -1) {
    perror("open fifo");
    exit(EXIT_FAILURE);
  }

  while ((bytes_read = read(fifo, buf, sizeof(buf))) > 0) {
    ssize_t bytes_written = write(output_file, buf, bytes_read);
    printf("Odczytano z potoku: %s\n", buf);
    if (bytes_written == -1) {
      perror("write output_file\n");
      close(output_file);
      close(fifo);
      exit(EXIT_FAILURE);
    }
    sleep(rand() % MAX_SLEEP_TIME);
  }
  close(output_file);
  close(fifo);
}
