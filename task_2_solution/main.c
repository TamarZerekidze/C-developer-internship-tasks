#include <unistd.h>
#include <dirent.h>
#include <stdio.h>

void printDIRContents(DIR *dir) {
	struct dirent* entry;
	while ((entry = readdir(dir))) {
		printf("%s\n", entry->d_name);
	}
}

int main(void) {
	char cwd[PATH_MAX];
	if (getcwd(cwd, sizeof(cwd)) == NULL) {
		perror("could not get cwd\n");
		return 1;
	}
	printf("%s\n", cwd);

	DIR *cwdDir;
	if ((cwdDir = opendir(cwd))) {
		printDIRContents(cwdDir);
		if (closedir(cwdDir)) {
			perror("could not close directory");
			return 1;
		}
	} else {
		perror("could not open directory");
		return 1;
	}

	return 0;
}