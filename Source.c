
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#define TOKEN 64
#define DELI " \t\a\r\n"

int launch(char **input) {
  int pid = 0, wpid = 0;
  int status;
  pid = fork();
  if (pid == 0) {
    if (execvp(input[0], input))
      ;
  } else if (pid < 0) {
    perror("no");
  } else {
    wpid = waitpid(pid, &status, WUNTRACED);
  }
}
char **parse(char *line) {
  int position = 0;
  int buffersize = TOKEN;
  char **tokens = malloc(buffersize * sizeof(char *));
  char *token;

  token = strtok(line, DELI);
  while (token) {
    tokens[position] = token;
    position++;
    if (position >= buffersize) {
      buffersize += TOKEN;
      tokens = realloc(tokens, buffersize * sizeof(char *));
    }

    token = strtok(NULL, DELI);
  }
  tokens[position] = NULL;
  return tokens;
}

char *read_line() {
  int buffersize = 64;
  int position = 0;
  char *buffer = (char *)malloc(buffersize * sizeof(char));
  int c;

  if (!buffer) {
    printf("error \n");
    exit();
  }

  while (1) {
    c = getchar();
    if (c == "\n" || c == EOF) {
      buffer[position] = '\0';
      return buffer;
    } else {
      buffer[position] = c;
      position++;
    }

    if (position >= buffersize) {
      buffersize *= 2;
      buffer = realloc(buffer, buffersize);
    }
  }
}
void loop() {
  int status;
  char *line;
  char **args;

  status = 1;

  do {
    printf("> ");

    line = read_line();
    args = parse(line);
    status = execute(args);
    printf(line);
    free(line);
    free(args);
  } while (status);
}
int main() { loop(); }
