#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
  pid_t pid, ppid, ret_id;
  int exit_status;

  ret_id = fork();

  if (ret_id == 0)
    printf("I'm a child, ");
  else
    printf("I'm a parent, ");

  pid = getpid();
  ppid = getppid();

  printf("my pid = %d, ppid = %d\n", pid, ppid);

  if (ret_id == 0) {
    exit(EXIT_SUCCESS);
  } else {
    ret_id = wait(&exit_status);
    printf("%d died with code %d\n", ret_id, exit_status);
  }

  return 0;
}
