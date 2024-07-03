#include "../include/bash.h"

void run_bash() {
  char input[MAX_INPUT];
  char* args[MAX_ARGS];

  while (1) {
    print_prompt();

    if (fgets(input, sizeof(input), stdin) == NULL) {
      break;
    }

    parse_input(input, args);

    if (args[0] == NULL) {
      continue;
    }

    if (strcmp(args[0], "exit") == 0) {
      break;
    } else if (strcmp(args[0], "cd") == 0) {
      change_directory(args);
    } else {
      execute_command(args);
    }
  }
}

void parse_input(char* input, char** args) {
  char* token;
  int i = 0;

  token = strtok(input, " \n");
  while (token != NULL && i < MAX_ARGS - 1) {
    args[i++] = token;
    token = strtok(NULL, " \n");
  }
  args[i] = NULL;
}

void execute_command(char** args) {
  pid_t pid = fork();

  if (pid < 0) {
    perror("fork failed");
    exit(EXIT_FAILURE);
  } else if (pid == 0) {
    if (execvp(args[0], args) < 0) {
      perror("exec failed");
      exit(EXIT_FAILURE);
    }
  } else {
    int status;
    if (waitpid(pid, &status, 0) < 0) {
      perror("waitpid failed");
    }
  }
}

void change_directory(char** args) {
  if (args[1] == NULL) {
    fprintf(stderr, "cd: expected argument to \"cd\"\n");
  } else {
    if (chdir(args[1]) != 0) {
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
