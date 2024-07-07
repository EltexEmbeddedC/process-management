#include "../include/bash.h"

void parse_input(char* input, char** commands) {
  char* token;
  int i = 0;

  token = strtok(input, "|");
  while (token != NULL && i < MAX_PIPES - 1) {
    commands[i++] = token;
    token = strtok(NULL, "|");
  }
  commands[i] = NULL;
}

void parse_command(char* command, char** args) {
  char* token;
  int i = 0;

  token = strtok(command, " \n");
  while (token != NULL && i < MAX_ARGS - 1) {
    args[i++] = token;
    token = strtok(NULL, " \n");
  }
  args[i] = NULL;
}

void execute_pipeline(char** commands) {
  int i = 0, in_fd = 0, fd[2];
  pid_t pid;
  int status;

  while (commands[i] != NULL) {
    pipe(fd);
    if ((pid = fork()) == -1) {
      perror("fork failed");
      exit(EXIT_FAILURE);
    } else if (pid == 0) {
      if (in_fd != 0) {
        dup2(in_fd, STDIN_FILENO);
        close(in_fd);
      }
      if (commands[i + 1] != NULL) {
        dup2(fd[1], STDOUT_FILENO);
      }
      close(fd[0]);
      close(fd[1]);

      char* args[MAX_ARGS];
      parse_command(commands[i], args);

      if (execvp(args[0], args) < 0) {
        perror("exec failed");
        exit(EXIT_FAILURE);
      }

    } else {
      waitpid(pid, &status, 0);
      close(fd[1]);
      in_fd = fd[0];
      i++;
    }
  }
}

void change_directory(char** args) {
  if (args[1] == NULL) {
    fprintf(stderr, "cd: expected argument to \"cd\"\n");
  } else {
    if (chdir(args[1]) != 0) {
      printf("\n\n%s\n\n", args[1]);
      perror("cd failed");
    }
  }
}

void print_prompt() {
  char cwd[MAX_INPUT];
  char* user = getpwuid(getuid())->pw_name;

  if (getcwd(cwd, sizeof(cwd)) != NULL) {
    printf("%s@%s: %s$ ", user, "shell", cwd);
  } else {
    perror("getcwd failed");
  }
}

void run_bash() {
  char input[MAX_INPUT];
  char* commands[MAX_PIPES];
  char* args[MAX_ARGS];

  while (1) {
    print_prompt();

    if (fgets(input, sizeof(input), stdin) == NULL) {
      break;
    }

    parse_input(input, commands);

    if (commands[0] == NULL) {
      continue;
    }

    if (strcmp(input, "exit\n") == 0) {
      break;
    } else if (commands[0][0] == 'c' && commands[0][1] == 'd' &&
               commands[0][2] == ' ') {
      parse_command(commands[0], args);
      change_directory(args);
    } else {
      execute_pipeline(commands);
    }
  }
}