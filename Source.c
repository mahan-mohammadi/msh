#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#define TOKEN 64
#define DELI " \t\a\r\n"
int cd(char **args);
int help(char **args);
int exit_sh(char **args);
int launch(char **);
char *builtin[] = {"cd", "help", "exit"};

int (*builtin_func[])(char **) = {&cd, &help, &exit_sh};

int num_builtins() { return sizeof(builtin) / sizeof(char *); }

int cd(char **args) {
  if (args[1] == NULL) {
    fprintf(stderr, "expected argument \n");
  } else {
    if (chdir(args[1]) != 0) { // checks if it return errors
      perror("lsh");
    }
  }
  return 1;
}
int exit_sh(char **args) { return 0; }

int help(char **) {
  printf("NO LOL \n");
  return 1;
}

int execute(char **args) {
  if (args[0] == NULL) {
    return 1;
  }
  for (int i = 0; i < num_builtins(); i++) {
    if (strcmp(args[0], builtin[i]) == 0) {
      return (*builtin_func[i])(args);
    }
  }

  return launch(args);
}

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
    do {
      wpid = waitpid(pid, &status, WUNTRACED);
    } while (!WIFEXITED(status) && !WIFSIGNALED(status));
  }
  return 1;
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
    exit(1);
  }

  while (1) {
    c = getchar();
    if (c == '\n' || c == EOF) {
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
    free(line);
    free(args);
  } while (status);
}
int main() { loop(); }
