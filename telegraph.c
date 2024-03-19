#include <time.h>
#include <ncurses.h>

#include "morse_tree.h"

int main() {

  // morse_branch tree[MAX_CODE_BRANCHES];
  // morse_tree_init(tree);
  // // morse_tree_test(tree);

  initscr();

  raw();
  noecho();

  for (;;) {
    // measure typing speed from last N gaps
    // get inputs
    // print dits/dahs
    // print translation below
    // feature: update translation based on context (error correction)
  
  	getch();

    refresh();
  }

	printw("Hello, World!");
	endwin();	

  return 0;
}
