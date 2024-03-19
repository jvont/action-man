#include "morse_tree.h"

#include <ctype.h>
#include <stdint.h>
#include <stdio.h>

#ifndef ARRAY_LEN
#define ARRAY_LEN(a) (sizeof(a) / sizeof(a[0]))
#endif

// morse code characters table
#define MORSE_CHAR_GEN(k, v) k,
const char morse_chars[] = {MORSE_CODE_MAP(MORSE_CHAR_GEN)};
#undef MORSE_CHAR_GEN

// morse code codes table
#define MORSE_CODE_GEN(k, v) v,
const uint16_t morse_codes[] = {MORSE_CODE_MAP(MORSE_CODE_GEN)};
#undef MORSE_CODE_GEN

void morse_branches_init(morse_branch **get, const int depth) {
  if (depth < MAX_CODE_LEN) {
    morse_branch *curr = *get;
    curr->dit = ++(*get);
    morse_branches_init(get, depth + 1);
    curr->dah = ++(*get);
    morse_branches_init(get, depth + 1);
  } else {
    (*get)->dit = NULL;
    (*get)->dah = NULL;
  }
}

void morse_tree_init(morse_branch tree[MAX_CODE_BRANCHES]) {
  // Build morse tree from given pool
  morse_branch *root = tree;
  morse_branches_init(&root, 0);

  // Match codes to branch nodes
  for (int c = 0; c < ARRAY_LEN(morse_codes); c++) {
    uint16_t code = morse_codes[c];
    morse_branch *curr = tree;
    for (int j = 0; j <= MAX_CODE_LEN; j++) {
      uint16_t mark = (code >> (14 - (2 * j))) & 0x3;
      if (mark == 0b01) {
        curr = curr->dit;
      } else if (mark == 0b11) {
        curr = curr->dah;
      } else {
        break;
      }
    }
    curr->ch = morse_chars[c];
  }
}

char morse_tree_search(morse_branch *curr, uint16_t code) {
  for (int i = 0; i <= MAX_CODE_LEN; i++) {
    uint16_t mark = (code >> (14 - (2 * i))) & 0x3;
    if (mark == 0b01) {
      curr = curr->dit;
    } else if (mark == 0b11) {
      curr = curr->dah;
    } else {
      break;
    }
  }
  return curr->ch;
}

void morse_code_str(const uint16_t code, char buf[MAX_CODE_LEN + 1]) {
  int i;
  for (i = 0; i < MAX_CODE_LEN; i++) {
    uint16_t mark = (code >> (14 - (2 * i))) & 0x3;
    if (mark == 0b01) {
      buf[i] = '.';
    } else if (mark == 0b11) {
      buf[i] = '-';
    } else {
      // end-of-code or error
      buf[i] = ' ';
      break;
    }
  }
  buf[i] = '\0';
}

uint16_t morse_char_code(const char c) {
  const char cup = toupper(c);
  for (int i = 0; i < ARRAY_LEN(morse_codes); i++) {
    if (morse_chars[i] == cup) {
      return morse_codes[i];
    }
  }
  return 0;
}

void morse_tree_print(const morse_branch *branch, const int depth) {
  for (int i = 0; i < 2 * depth; i++) {
    putc(' ', stdout);
  }
  printf("|-%c\n", branch->ch);

  if (branch->dit) {
    morse_tree_print(branch->dit, depth + 1);
  }
  if (branch->dah) {
    morse_tree_print(branch->dah, depth + 1);
  }
}

void morse_tree_test(morse_branch *tree) {
  char buf[MAX_CODE_LEN + 1];
  uint16_t code;
  char c;

  // Print codes
  for (int i = 0; i < ARRAY_LEN(morse_chars); i++) {
    code = morse_codes[i];

    morse_code_str(code, buf);
    printf("%c: %s\n", morse_chars[i], buf);
  }

  // Lookup code
  code = 0b0111000000000000;
  c = morse_tree_search(tree, code);
  morse_code_str(code, buf);
  printf("%c: %s\n", c, buf);

  // Lookup char
  c = 'a';
  code = morse_char_code(c);
  morse_code_str(code, buf);
  printf("%c: %s\n", c, buf);
}
