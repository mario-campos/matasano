#include <assert.h>
#include <string.h>
#include "hex.h"

static inline uint8_t hexord(const char c) {
  assert((c >= '0' && c <= '9')
      || (c >= 'a' && c <= 'f')
      || (c >= 'A' && c <= 'F'));
  const uint8_t lookup[] = {
    ['0'] = 0,
    ['1'] = 1,
    ['2'] = 2,
    ['3'] = 3,
    ['4'] = 4,
    ['5'] = 5,
    ['6'] = 6,
    ['7'] = 7,
    ['8'] = 8,
    ['9'] = 9,
    ['a'] = 0xA, ['A'] = 0xA,
    ['b'] = 0xB, ['B'] = 0xB,
    ['c'] = 0xC, ['C'] = 0xC,
    ['d'] = 0xD, ['D'] = 0xD,
    ['e'] = 0xE, ['E'] = 0xE,
    ['f'] = 0xF, ['F'] = 0xF
  };
  return lookup[c];
}

static inline char hexchar(const uint8_t ord) {
  assert(ord >= 0 && ord <= 15);
  const char lookup[] = "0123456789abcdef";
  return lookup[ord];
}

size_t hextobin(const char * restrict hex, uint8_t * restrict bin) {
  const size_t len = strlen(hex);

  if (len % 2 != 0) {
    *bin++ = hexord(*hex++);
  }

  while(*hex) {
    *bin = (hexord(hex[0]) << 4) | hexord(hex[1]);
    hex += 2; bin++;
  }

  return (len / 2) + (len % 2);
}

void bintohex(const uint8_t * restrict bin, const size_t size,
              char * restrict hex) {
  for(size_t i = 0; i < size; i++) {
    *hex++ = hexchar(bin[i] >> 4);
    *hex++ = hexchar(bin[i] & 0x0F);
  }
  *hex = '\0';
}
