#include "../include/message_queue.h"

#include <fcntl.h>
#include <mqueue.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

int create_queue(Queue *queue, const char *name) {
  struct mq_attr attr;
  attr.mq_flags = 0;
  attr.mq_maxmsg = 10;
  attr.mq_msgsize = MAX_EXPRESSION_LENGTH;

  queue->descriptor = mq_open(name, O_CREAT | O_RDONLY | O_EXCL, 0666, &attr);
  if (queue->descriptor == (mqd_t)-1) {
    return 0;
  }

  strcpy(queue->name, name);

  return 1;
}

int open_queue(Queue *queue, const char *name) {
  queue->descriptor = mq_open(name, O_WRONLY);
  if (queue->descriptor == (mqd_t)-1) {
    return 0;
  }

  strcpy(queue->name, name);

  return 1;
}

int send_message(Queue *queue, const char *message) {
  if (mq_send(queue->descriptor, message, strlen(message), 0) == -1) {
    return 0;
  }

  return 1;
}

int receive_message(Queue *queue, char *buffer) {
  if (mq_receive(queue->descriptor, buffer, MAX_EXPRESSION_LENGTH, NULL) == -1) {
    return 0;
  }

  return 1;
}

void close_queue(Queue *queue) {
  mq_close(queue->descriptor);
}

void remove_queue(Queue *queue) {
  mq_unlink(queue->name);
}