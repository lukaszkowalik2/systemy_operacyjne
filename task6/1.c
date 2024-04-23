#include <fcntl.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

#include "mylib.h"

int main(int argc, char *argv[]) {
  double cos = 12312312.21312312;
  double cos2 = 123123213;
  double ww = myFun(cos, cos2);
  printf("%f\n", ww);
  exit(EXIT_SUCCESS);
}