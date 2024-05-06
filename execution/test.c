# include <dirent.h>
# include <string.h>
#include <stdio.h>

int main() {
  DIR *dir;
  struct dirent *entry;

  dir = opendir("builtins/");

  if (dir == NULL) {
    perror("opendir");
    return 1;
  }

  while ((entry = readdir(dir)) != NULL) {
    if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
      continue; // Skip "." and ".."
    }
    printf("%s\n", entry->d_name);
  }

  closedir(dir);

  return 0;
}
