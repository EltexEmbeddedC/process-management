#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

void print_process_info(int number) {
  printf("process%d: pid = %d, ppid = %d\n", number, getpid(), getppid());
}

int main() {
  pid_t ret_pid;
  int exit_status;
  print_process_info(0);

  if (fork() == 0) {
    print_process_info(1);

    if (fork() == 0) {
      print_process_info(3);
      exit(3);
    }

    if (fork() == 0) {
      print_process_info(4);
      exit(4);
    }

    ret_pid = wait(&exit_status);
    printf("message from 1: process%d died (pid = %d)\n",
           WEXITSTATUS(exit_status), ret_pid);

    ret_pid = wait(&exit_status);
    printf("message from 1: process%d died (pid = %d)\n",
           WEXITSTATUS(exit_status), ret_pid);

    exit(1);
  }

  if (fork() == 0) {
    print_process_info(2);

    if (fork() == 0) {
      print_process_info(5);
      exit(5);
    }

    ret_pid = wait(&exit_status);
    printf("message from 2: process%d died (pid = %d)\n",
           WEXITSTATUS(exit_status), ret_pid);

    exit(2);
  }

  ret_pid = wait(&exit_status);
  printf("message from 0: process%d died (pid = %d)\n",
         WEXITSTATUS(exit_status), ret_pid);

  ret_pid = wait(&exit_status);
  printf("message from 0: process%d died (pid = %d)\n",
         WEXITSTATUS(exit_status), ret_pid);

  return 0;
}
