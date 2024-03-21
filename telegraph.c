#include <ncurses.h>
#include <time.h>

#include <SDL3/SDL.h>

#include "morse_tree.h"

int kbhit(void) {
  int ch = getch();

  if (ch != ERR) {
    ungetch(ch);
    return 1;
  } else {
    return 0;
  }
}

int main() {

  // morse_branch tree[MAX_CODE_BRANCHES];
  // morse_tree_init(tree);
  // // morse_tree_test(tree);

  initscr();

  cbreak();
  // raw();
  noecho();
  // nodelay(stdscr, TRUE);
  timeout(100);
  scrollok(stdscr, TRUE);

  int ch, prev;
  struct timespec t0, t1;
  long dt;

  for (;;) {
    // measure typing speed from last N gaps
    // get inputs
    // print dits/dahs
    // print translation below
    // feature: update translation based on context (error correction)

    // if (clock_gettime(CLOCK_MONOTONIC, &t0) < 0) {
    //   perror("clock_gettime()");
    // }

    ch = getch();
    if (ch == '\e') {
      break;
    }

    if (ch != -1) {
      mvaddch(0, 0, ch);

      // ungetch(ch);
    } else {
      mvaddch(0, 0, ' ');
    }

    if (ch == -1) {
      mvaddch(1, 0, 'x');
    } else {
      mvaddch(1, 0, ' ');
    }

    // mvaddch(3, 3, ch);
    // mvaddch(1, 1, ch == -1 ? 'x' : ' ');

    // if (ch == ' ') {
    //   mvaddch(0, 0, '1');
    //   clock_gettime(CLOCK_MONOTONIC, &t0);
    // } else if (ch != ' ') {
    //   mvaddch(0, 0, '0');
    // }

    // mvaddch(0, 2, ch == -1 ? 'x' : ' ');

    // if (ch == ' ') {

    //   clock_gettime(CLOCK_MONOTONIC, &t1);
    //   dt = (t1.tv_sec - t0.tv_sec) * 1000L +
    //        (t1.tv_nsec - t0.tv_nsec) / 1000000L;

    //   // mvprintw(1, 1, "%ld", dt);
    //   mvprintw(1, 1, "%ld", dt);

    //   // if (((1000 * dt) / CLOCKS_PER_SEC) < 250) {
    //   //   addch('.');
    //   // } else {
    //   //   addch('-');
    //   // }
    // }
    // prev = ch;

    refresh();
  }

  endwin();

  return 0;
}
