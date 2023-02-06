//#define _GNU_SOURCE /* for O_PATH */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>

#ifndef O_PATH
#define O_PATH 0
#endif

int main(int argc, char **argv) {
  if (argc < 2) {
    printf("Usage: %s DIR FILE_IN_DIR\n", argv[0]);
    exit(1);
  }

  const char *dir_name = argv[1];
  const char *file_name = argv[2];

  int dir_fd = open(dir_name, O_RDONLY | O_DIRECTORY | O_PATH);
  if (dir_fd < 0) {
    printf("ERROR: Failed to open directory: %s: %s\n", dir_name, strerror(errno));
    exit(1);
  }

  puts("Sleeping after opening directory...");
  sleep(5);

  int file_fd = openat(dir_fd, file_name, O_RDONLY);
  if (file_fd < 0) {
    printf("ERROR: Failed to open file: %s: %s\n", file_name, strerror(errno));
    exit(1);
  }

  char buf[256];
  int read_size = read(file_fd, buf, sizeof(buf));
  if (read_size < 0) {
    printf("ERROR: Failed to read file: %s: %s\n", file_name, strerror(errno));
    exit(1);
  }

  puts("Sleeping after opening file...");
  sleep(5);

  int write_size = write(STDOUT_FILENO, buf, read_size);
  if (write_size < 0) {
    printf("ERROR: Failed to write to stdout: %s\n", strerror(errno));
    exit(1);
  }

  exit(0);
}
