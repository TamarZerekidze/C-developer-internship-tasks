#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

void exec_program(const char *prog) {
	execl(prog, prog, NULL);
	perror("execl failed");
	exit(1);
}

int my_fork() {
	const int pid = fork();
	if (pid == -1) {
		perror("fork failed");
		exit(1);
	}
	return pid;
}

int main(int argc, char *argv[]) {
	if (argc != 5) {
		exit(1);
	}

	const char *prog1 = argv[1];
	const char *prog2 = argv[2];
	const char *prog3 = argv[3];
	const char *file = argv[4];

	if (my_fork() == 0) {
		exec_program(prog1);
	}

	int status1;
	wait(&status1);
	if (status1 != 0) {
		exit(1);
	}

	int fds[2];
    if (pipe(fds) < 0) {
    	perror("pipe failed");
    	exit(1);
    }

	if (my_fork() == 0) {
		close(fds[0]);
		dup2(fds[1], 1);
		close(fds[1]);
		exec_program(prog2);
	}

	if (my_fork() == 0) {
		close(fds[1]);
		dup2(fds[0], 0);
		close(fds[0]);

		const int fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd == -1) {
			perror("open error");
			exit(1);
		}
		dup2(fd, 1);
		close(fd);

		exec_program(prog3);
	}

	close(fds[0]);
	close(fds[1]);
	wait(NULL);
	wait(NULL);
}