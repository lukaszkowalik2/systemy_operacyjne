#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "./include/message_queue.h"

void handle_sigint(int sig) {
  printf("\nWyjście...\n");
  exit(EXIT_SUCCESS);
}

Queue client_queue;
Queue server_queue;

void close_queue_on_exit() {
  remove_queue(&client_queue);
  close_queue(&server_queue);
}

int main() {
  signal(SIGINT, handle_sigint);
  atexit(close_queue_on_exit);

  char queue_name[QUEUE_NAME_LENGTH];
  snprintf(queue_name, QUEUE_NAME_LENGTH, "/%d", getpid());
  if (!create_queue(&client_queue, queue_name)) {
    fprintf(stderr, "Błąd podczas tworzenia kolejki klienta\n");
    exit(EXIT_FAILURE);
  }

  if (!open_queue(&server_queue, QUEUE_NAME)) {
    fprintf(stderr, "Błąd podczas otwierania kolejki serwera\n");
    exit(EXIT_FAILURE);
  } else {
    printf("Klient zainicjowany z PID: %d\n", getpid());
  }

  char expression[MAX_EXPRESSION_LENGTH];
  printf("Wprowadź wyrażenie arytmetyczne (np. 2+3): ");
  while (fgets(expression, MAX_EXPRESSION_LENGTH, stdin) != NULL) {
    char message[MAX_EXPRESSION_LENGTH + 50];
    snprintf(message, sizeof(message), "/%d %s", getpid(), expression);

    printf("Wysyłanie wyrażenia: %s", message);
    if (!send_message(&server_queue, message)) {
      fprintf(stderr, "Błąd podczas wysyłania wiadomości do serwera\n");
      break;
    }

    char response[MAX_EXPRESSION_LENGTH];
    if (!receive_message(&client_queue, response)) {
      fprintf(stderr, "Błąd podczas odbierania wiadomości od serwera\n");
      break;
    }

    printf("Wynik: %s\n", response);
    printf("Wprowadź wyrażenie arytmetyczne (np. 2+3): ");
  }

  remove_queue(&client_queue);
  close_queue(&server_queue);

  return 0;
}