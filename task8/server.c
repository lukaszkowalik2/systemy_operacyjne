#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "./include/message_queue.h"

Queue client_queue;
Queue server_queue;

void close_queue_on_exit() {
  remove_queue(&server_queue);
}

void handle_sigint(int sig) {
  printf("\nWyjście...\n");
  exit(EXIT_SUCCESS);
}

int main() {
  signal(SIGINT, handle_sigint);
  atexit(close_queue_on_exit);

  if (!create_queue(&server_queue, QUEUE_NAME)) {
    fprintf(stderr, "Błąd podczas tworzenia kolejki\n");
    exit(EXIT_FAILURE);
  } else {
    fprintf(stderr, "Serwer włączony\n");
  }

  char expression[MAX_EXPRESSION_LENGTH];

  while (1) {
    if (!receive_message(&server_queue, expression)) {
      fprintf(stderr, "Błąd pobieranie wiadomości\n");
      break;
    }
    printf("Otrzymano wyrażenie: %s\n", expression);
    char client_queue_name[50];
    char* space_pos = strchr(expression, ' ');
    if (space_pos == NULL) {
      fprintf(stderr, "Błąd: wyrażenie nie zawiera spacji\n");
      exit(EXIT_FAILURE);
    }

    int length = space_pos - expression;
    strncpy(client_queue_name, expression, length);
    client_queue_name[length] = '\0';

    Queue client_queue;
    if (!open_queue(&client_queue, client_queue_name)) {
      fprintf(stderr, "Błąd otwarcia kolejki klienta\n");
      exit(EXIT_FAILURE);
    }

    char operator;
    int num1, num2;
    sscanf(expression + strlen(client_queue_name) + 1, "%d %c %d", &num1, &operator, & num2);
    int result;
    switch (operator) {
      case '+': {
        result = num1 + num2;
        break;
      }
      case '-': {
        result = num1 - num2;
        break;
      }
      case '*': {
        result = num1 * num2;
        break;
      }
      case '/': {
        result = num1 / num2;
        break;
      }
      default: {
        sprintf(expression, "Nieprawidłowy operator");
        send_message(&client_queue, expression);
        close_queue(&client_queue);
        exit(EXIT_FAILURE);
      }
    }

    printf("Wysyłanie: %d\n", result);
    sprintf(expression, "%d", result);
    send_message(&client_queue, expression);
    close_queue(&client_queue);
  }

  close_queue(&server_queue);
  remove_queue(&server_queue);
  exit(EXIT_SUCCESS);
}