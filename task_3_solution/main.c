#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
	if (argc != 4) {
		exit(1);
	}

	const char *prog1 = argv[1];
	const char *prog2 = argv[2];
	const char *prog3 = argv[3];

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
	int fds[2];
	pipe(fds);
	if (fork() == 0) {
		close(fds[0]);
		dup2(fds[1], 1);
		close(fds[1]);
		execl(prog2, prog2, NULL);
		perror("execl prog2 failed");
		exit(1);
	}
	if (fork() == 0) {
		close(fds[1]);
		dup2(fds[0], 0);
		close(fds[0]);
		execl(prog3, prog3, NULL);
		perror("execl prog3 failed");
		exit(1);
	}
	close(fds[0]);
	close(fds[1]);
	wait(NULL);
	wait(NULL);
}