#include <fcntl.h>
#include <mqueue.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

#include "mylib.h"

int main(int argc, char *argv[]) {
  mqd_t mq = mq_open(QUEUE_NAME, O_WRONLY);
  if (mq == -1) {
    perror("mq_open client");
    exit(EXIT_FAILURE);
  }

  // mq_close(QUEUE_NAME);
  exit(EXIT_SUCCESS);
}