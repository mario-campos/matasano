#include <stdio.h>
#include <string.h>
#include "hex.h"
#include "xor.h"

static inline size_t min(size_t a, size_t b) {
  if (a < b) {
    return a;
  } else {
    return b;
  }
}

void xorhex(const char * restrict a, const char * restrict b, char * restrict c) {
  const size_t size = min(strlen(a), strlen(b)) / 2;
  uint8_t a_buf[size], b_buf[size], c_buf[size];
  hextobin(a, a_buf);
  hextobin(b, b_buf);
  xor(a_buf, b_buf, c_buf, size);
  bintohex(c_buf, size, c);
}

int main() {
  const char *a = "1c0111001f010100061a024b53535009181c"; 
  const char *b = "686974207468652062756c6c277320657965";
  char c[strlen(a)];
  xorhex(a, b, c);
  puts(c);
}
