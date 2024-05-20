#ifndef MESSAGE_QUEUE_H
#define MESSAGE_QUEUE_H

#include <mqueue.h>
#include <string.h>

#define QUEUE_NAME_LENGTH 50
#define MAX_EXPRESSION_LENGTH 50
#define QUEUE_NAME "/server_queue"

typedef struct {
  char name[QUEUE_NAME_LENGTH];
  mqd_t descriptor;
} Queue;

int create_queue(Queue *queue, const char *name);
int open_queue(Queue *queue, const char *name);
int send_message(Queue *queue, const char *message);
int receive_message(Queue *queue, char *buffer);
void close_queue(Queue *queue);
void remove_queue(Queue *queue);

#endif
