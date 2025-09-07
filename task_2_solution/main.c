#include <unistd.h>
#include <dirent.h>
#include <stdio.h>
#include <string.h>

int isHidden(const struct dirent* entry) {
	return entry->d_name[0] == '.';
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

			DIR *newDir;
			if ((newDir = opendir(new_path))) {
				printDIRContents(newDir, new_path);
				if (closedir(newDir)) {
					perror("could not close directory");
				}
			} else {
				perror("could not open directory");
			}
		}
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
		printDIRContents(cwdDir, cwd);
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