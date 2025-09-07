#include <unistd.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void printDIRContents(DIR *dir, const char* current_path);

int isHidden(const struct dirent* entry) {
	return entry->d_name[0] == '.';
}

void visitDIR(const char *dir_path) {
	DIR *dir;

	if ((dir = opendir(dir_path))) {
		printDIRContents(dir, dir_path);

		if (closedir(dir)) {
			perror("could not close directory");
			exit(1);
		}
	} else {
		perror("could not open directory");
		exit(1);
	}
}

void printDIRContents(DIR *dir, const char* current_path) {
	struct dirent* entry;
	while ((entry = readdir(dir))) {
		if (isHidden(entry)) continue;
		printf("%s\n", entry->d_name);

		if (entry->d_type == DT_DIR) {
			char new_path[PATH_MAX];
			strcpy(new_path, current_path);
			strcat(new_path, "/");
			strcat(new_path, entry->d_name);

			visitDIR(new_path);
		}
	}
}

int main(void) {
	char cwd[PATH_MAX];
	if (getcwd(cwd, sizeof(cwd)) == NULL) {
		perror("could not get cwd\n");
		exit(1);
	}
	printf("%s\n", cwd);

	visitDIR(cwd);

	return 0;
}