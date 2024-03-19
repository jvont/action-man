#ifndef MORSE_TREE_H
#define MORSE_TREE_H

#include <stdint.h>

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

// morse code character tree
typedef struct morse_branch_t {
  char ch;
  struct morse_branch_t *dit, *dah;
} morse_branch;

// maximum branches is equal to 2^(max_len + 1) - 1
#define MAX_CODE_BRANCHES ((1 << (MAX_CODE_LEN + 1)) - 1)

void morse_branches_init(morse_branch **get, const int depth);
void morse_tree_init(morse_branch tree[MAX_CODE_BRANCHES]);
char morse_tree_search(morse_branch *curr, uint16_t code);
void morse_code_str(const uint16_t code, char buf[MAX_CODE_LEN + 1]);
uint16_t morse_char_code(const char c);
void morse_tree_print(const morse_branch *branch, const int depth);
void morse_tree_test(morse_branch *tree);

#endif
