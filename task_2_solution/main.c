#include <unistd.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void printDIRContents(DIR *dir, char* current_path, int level);

int isHidden(const struct dirent* entry) {
	return entry->d_name[0] == '.';
}

void fillTabs(char *tabs, const int level) {
	for (int i = 0; i < level; i++) {
		tabs[i] = '\t';
	}
	tabs[level] = '\0';
}

void visitDIR(char *dir_path, const int level) {
	DIR *dir;

	if ((dir = opendir(dir_path))) {
		printDIRContents(dir, dir_path, level + 1);

		if (closedir(dir)) {
			perror("could not close directory");
			exit(1);
		}
	} else {
		perror("could not open directory");
		exit(1);
	}
}

void removeLastSubDir(char *dir_path) {
	const int len = strlen(dir_path);
	for (int i = len - 1; i >= 0; i--) {
		if (dir_path[i] == '/') {
			dir_path[i] = '\0';
			return;
		}
		dir_path[i] = '\0';
	}
}

void printDIRContents(DIR *dir, char* current_path, const int level) {
	struct dirent* entry;
	while ((entry = readdir(dir))) {
		if (isHidden(entry)) continue;

		char tabs[level + 1];
		fillTabs(tabs, level);
		printf("%s%s\n", tabs, entry->d_name);

		if (entry->d_type == DT_DIR) {
			strcat(current_path, "/");
			strcat(current_path, entry->d_name);
			visitDIR(current_path, level);
			removeLastSubDir(current_path);
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

	visitDIR(cwd, 0);

	return 0;
}