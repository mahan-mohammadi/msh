#include <stdio.h>
void loop() {
	int status;
	char* line;
	char** args;

	do {
		printf("> ");

		line = read_line();
		args = parse(line);
		status = execute(args);
	} while (status);
}
int main() {
	loop();
}

