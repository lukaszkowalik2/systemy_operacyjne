/*
  Program ten ma za zadanie wypisać identyfikatory UID, GID, PID, PPID i PGID dla bieżącego procesu.
  ----------------------------------------------------------------------
  Autor: Łukasz Kowalik
  ----------------------------------------------------------------------
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
  int pid = getpid();
  int gid = getgid();
  int uid = getuid();
  int ppid = getppid();
  int pgid = getpgid(0);

  printf("UID: %d, GID: %d, PID: %d, PPID: %d, PGID: %d\n", uid, gid, pid, ppid, pgid);

  exit(EXIT_SUCCESS);
}