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
  int pgid = getpgid(pid);
  int pgrp = getpgrp();

  fprintf(stderr, "pid=%d; gid=%d; uid=%d; ppid=%d; pgid=%d; pgrp=%d\n", pid, gid, uid, ppid, pgid, pgrp);

  exit(EXIT_SUCCESS);
}