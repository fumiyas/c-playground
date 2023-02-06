#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char **argv) {
  int fd;
  fd = shm_open("xxxxx", O_CREAT | O_RDWR | O_EXCL, 0666);
  if (fd < 0) {
    printf("fd=%d, error=%s\n", fd, strerror(errno));
  }
  sleep(10);
}
