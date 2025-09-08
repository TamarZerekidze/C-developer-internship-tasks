#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
	if (argc != 3) {
		exit(1);
	}

	const char *prog1 = argv[1];
	const char *prog2 = argv[2];

	if (fork() == 0) {
		execl(prog1, prog1, NULL);
		perror("execl prog1 failed");
		exit(1);
	}

	int status1;
	wait(&status1);
	if (status1 != 0) {
		exit(1);
	}

	if (fork() == 0) {
		execl(prog2, prog2, NULL);
		perror("execl prog2 failed");
		exit(1);
	}

	wait(NULL);
	exit(0);
}