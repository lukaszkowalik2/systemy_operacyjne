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
    printf("Użycie: %s <read_file> <fifo_path>\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  char buf[BUF_SIZE];
  size_t bytes_read;

  int read_file = open(argv[1], O_RDONLY);
  if (read_file == -1) {
    perror("open read_file");
    exit(EXIT_FAILURE);
  }

  int fifo = open(argv[2], O_WRONLY);
  if (fifo == -1) {
    perror("open fifo");
    exit(EXIT_FAILURE);
  }

  while ((bytes_read = read(read_file, buf, sizeof(buf))) > 0) {
    ssize_t bytes_written = write(fifo, buf, bytes_read);
    printf("Wysłano do potoku: %s\n", buf);
    if (bytes_written == -1) {
      perror("write input_file\n");
      close(read_file);
      close(fifo);
      exit(EXIT_FAILURE);
    }
    sleep(rand() % MAX_SLEEP_TIME);
  }
  close(read_file);
  close(fifo);
}