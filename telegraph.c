#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <time.h>

#ifndef ARRAY_LEN
#define ARRAY_LEN(a) (sizeof(a) / sizeof(a[0]))
#endif

// ascii to morse code sequence encoding
#define MORSE_CODE_MAP(GEN)                                                    \
  GEN('A', 0b0111000000000000)                                                 \
  GEN('B', 0b1101010100000000)                                                 \
  GEN('C', 0b1101110100000000)                                                 \
  GEN('D', 0b1101010000000000)                                                 \
  GEN('E', 0b0100000000000000)                                                 \
  GEN('F', 0b0101110100000000)                                                 \
  GEN('G', 0b1111010000000000)                                                 \
  GEN('H', 0b0101010100000000)                                                 \
  GEN('I', 0b0101000000000000)                                                 \
  GEN('J', 0b0111111100000000)                                                 \
  GEN('K', 0b1101110000000000)                                                 \
  GEN('L', 0b0111010100000000)                                                 \
  GEN('M', 0b1111000000000000)                                                 \
  GEN('N', 0b1101000000000000)                                                 \
  GEN('O', 0b1111110000000000)                                                 \
  GEN('P', 0b0111110100000000)                                                 \
  GEN('Q', 0b1111011100000000)                                                 \
  GEN('R', 0b0111010000000000)                                                 \
  GEN('S', 0b0101010000000000)                                                 \
  GEN('T', 0b1100000000000000)                                                 \
  GEN('U', 0b0101110000000000)                                                 \
  GEN('V', 0b0101011100000000)                                                 \
  GEN('W', 0b0111110000000000)                                                 \
  GEN('X', 0b1101011100000000)                                                 \
  GEN('Y', 0b1101111100000000)                                                 \
  GEN('Z', 0b1111010100000000)                                                 \
  GEN('1', 0b0111111111000000)                                                 \
  GEN('2', 0b0101111111000000)                                                 \
  GEN('3', 0b0101011111000000)                                                 \
  GEN('4', 0b0101010111000000)                                                 \
  GEN('5', 0b0101010101000000)                                                 \
  GEN('6', 0b1101010101000000)                                                 \
  GEN('7', 0b1111010101000000)                                                 \
  GEN('8', 0b1111110101000000)                                                 \
  GEN('9', 0b1111111101000000)                                                 \
  GEN('0', 0b1111111111000000)

// maximum code length (10 bits for numbers)
#define MAX_CODE_LEN 5

// morse code characters table
#define MORSE_CHAR_GEN(k, v) k,
const char morse_chars[] = {MORSE_CODE_MAP(MORSE_CHAR_GEN)};
#undef MORSE_CHAR_GEN

// morse code codes table
#define MORSE_CODE_GEN(k, v) v,
const uint16_t morse_codes[] = {MORSE_CODE_MAP(MORSE_CODE_GEN)};
#undef MORSE_CODE_GEN

// morse code character tree
typedef struct morse_branch_t {
  char ch;
  struct morse_branch_t *dit, *dah;
} morse_branch;

// maximum branches is equal to 2^(max_len + 1) - 1
#define MAX_CODE_BRANCHES ((1 << (MAX_CODE_LEN + 1)) - 1)

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

int main() {

  morse_branch tree[MAX_CODE_BRANCHES];
  morse_tree_init(tree);
  // morse_tree_test(tree);

  int c;
  while ((c = getchar()) != 27 /* ASCII ESC */) {
    if (c < 0) {
      if (ferror(stdin)) {
        // handle error
      }
      clearerr(stdin);
    } else {
      /* some key OTHER than ESC was hit, do something about it? */
      printf("\b");
      printf(".");
      fflush(stdout);
    }
  }

  return 0;
}
