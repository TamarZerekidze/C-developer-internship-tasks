#include <unistd.h>
#include <dirent.h>
#include <stdio.h>

int main(void) {
	char cwd[PATH_MAX];
	if (getcwd(cwd, sizeof(cwd)) == NULL) {
		perror("could not get cwd\n");
		return 1;
	}
	printf("%s\n", cwd);
	return 0;
}