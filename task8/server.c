#include <fcntl.h>
#include <mqueue.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

#include "mylib.h"

int main(int argc, char *argv[]) {
  struct mq_attr attr = {0, 10, MAX_SIZE, 0};
  mqd_t mq = mq_open(QUEUE_NAME, O_RDONLY | O_CREAT | O_EXCL, 0777, &attr);
  if (mq == -1) {
    perror("mq_open server");
    exit(EXIT_FAILURE);
  }
  mq_unlink(QUEUE_NAME);
  exit(EXIT_SUCCESS);
}