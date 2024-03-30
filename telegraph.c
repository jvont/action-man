#include <fcntl.h> // open
#include <linux/kd.h>
#include <linux/keyboard.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <time.h>
#include <unistd.h> // read

#include "morse_tree.h"

int kd_raw_init() {}

int main() {
  // morse_branch tree[MAX_CODE_BRANCHES];
  // morse_tree_init(tree);
  // morse_tree_test(tree);

  int ch, prev;
  struct timespec t0, t1;
  long dt;

  int fd = open("/dev/tty0", O_RDONLY);
  printf("opened %d\n", fd);

  char buf[16];

  struct termios new;
  tcgetattr(fd, &new);

  new.c_lflag &= ~(ICANON | ECHO | ISIG);
  new.c_iflag = 0;
  new.c_cc[VMIN] = sizeof(buf);
  new.c_cc[VTIME] = 1; /* 0.1 sec intercharacter timeout */

  tcsetattr(fd, TCSAFLUSH, &new);
  ioctl(fd, KDSKBMODE, K_MEDIUMRAW);

  for (;;) {
    // measure typing speed from last N gaps
    // get inputs
    // print dits/dahs
    // print translation below
    // feature: update translation based on context (error correction)

    // if (clock_gettime(CLOCK_MONOTONIC, &t0) < 0) {
    //   perror("clock_gettime()");
    // }

    int n = read(fd, buf, sizeof(buf));
    printf("Read: %d\n", n);
    int i = 0;
    while (i < n) {
      int kc;
      char *s;

      s = (buf[i] & 0x80) ? "release" : "press";

      if (i + 2 < n && (buf[i] & 0x7f) == 0 && (buf[i + 1] & 0x80) != 0 &&
          (buf[i + 2] & 0x80) != 0) {
        kc = ((buf[i + 1] & 0x7f) << 7) | (buf[i + 2] & 0x7f);
        i += 3;
      } else {
        kc = (buf[i] & 0x7f);
        i++;
      }
      printf("keycode %3d %s\n", kc, s);

      if (kc == 1) {
        exit(0);
      }
    }
  }

  return 0;
}
