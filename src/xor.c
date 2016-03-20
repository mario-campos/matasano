#include "xor.h"

void xor(uint8_t *a, uint8_t *b, uint8_t *c, size_t size) {
  for(size_t i = 0; i < size; i++) {
    c[i] = a[i] ^ b[i];
  }
}
