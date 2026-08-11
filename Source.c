#include <stdio.h>
char* read_line() {
	int buffersize = 64;
	int position = 0;
	char* buffer = (char*)malloc(buffersize * sizeof(char));
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
		}
		else {
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
	char* line;
	char** args;

	do {
		printf("> ");

		line = read_line();
		args = parse(line);
		status = execute(args);

		free(line);
		free(args);
	} while (status);
}
int main() {
	loop();
}

