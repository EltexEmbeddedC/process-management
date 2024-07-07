#ifndef BASH_H
#define BASH_H

#include <errno.h>
#include <pwd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define MAX_INPUT 1024
#define MAX_ARGS 64
#define MAX_PIPES 10

void run_bash();
void parse_input(char* input, char** args);
void parse_command(char* command, char** args);
void execute_command(char** args);
void execute_pipeline(char** commands);
void change_directory(char** args);
void print_prompt();

#endif  // BASH_H
