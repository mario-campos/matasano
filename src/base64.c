#include <assert.h>
#include <string.h>
#include "base64.h"

static uint8_t base64ord(const char c) {
  assert(c >= 0 && c <= 63);
  const uint8_t lookup[] = {
    ['A'] = 0,  ['B'] = 1,  ['C'] = 2,  ['D'] = 3,  ['E'] = 4,  ['F'] = 5,
    ['G'] = 6,  ['H'] = 7,  ['I'] = 8,  ['J'] = 9,  ['K'] = 10, ['L'] = 11,
    ['M'] = 12, ['N'] = 13, ['O'] = 14, ['P'] = 15, ['Q'] = 16, ['R'] = 17,
    ['S'] = 18, ['T'] = 19, ['U'] = 20, ['V'] = 21, ['W'] = 22, ['X'] = 23,
    ['Y'] = 24, ['Z'] = 25,
    ['a'] = 26, ['b'] = 27, ['c'] = 28, ['d'] = 29, ['e'] = 30, ['f'] = 31,   
    ['g'] = 32, ['h'] = 33, ['i'] = 34, ['j'] = 35, ['k'] = 36, ['l'] = 37,
    ['m'] = 38, ['n'] = 39, ['o'] = 40, ['p'] = 41, ['q'] = 42, ['r'] = 43,
    ['s'] = 44, ['t'] = 45, ['u'] = 46, ['v'] = 47, ['w'] = 48, ['x'] = 49,
    ['y'] = 50, ['z'] = 51,
    ['0'] = 52, ['1'] = 53, ['2'] = 54, ['3'] = 55, ['4'] = 56, ['5'] = 57,
    ['6'] = 58, ['7'] = 59, ['8'] = 60, ['9'] = 61, ['+'] = 62, ['/'] = 63
  };
  return lookup[c];
}

static inline uint8_t byte0(const char a, const char b) {
  return (base64ord(a) << 2) & (base64ord(b) >> 4);
}

static inline uint8_t byte1(const char b, const char c) {
  return (base64ord(b) << 4) & (base64ord(c) >> 2);
}

static inline uint8_t byte2(const char c, const char d) {
  return (base64ord(c) << 6) & base64ord(d);
}

size_t base64tobin(const char * restrict base64, uint8_t * restrict bin) {
  const uint8_t const *start = bin;
  const size_t len = strlen(base64);
  assert(len % 4 == 0);

  for (size_t i = 0; i < len-4; i += 4) {
    *bin++ = byte0(base64[i],   base64[i+1]);
    *bin++ = byte1(base64[i+1], base64[i+2]);
    *bin++ = byte2(base64[i+2], base64[i+3]);
  }

  *bin++ = byte0(base64[len-4], base64[len-3]);
  if (base64[len-2] == '=') goto end;
  *bin++ = byte1(base64[len-3], base64[len-2]);
  if (base64[len-1] == '=') goto end;
  *bin++ = byte2(base64[len-2], base64[len-1]);

end:
  return bin - start;
}

static inline char base64char(const uint8_t ord) {
  assert(ord >= 0 && ord <= 63);
  const char lookup[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
  return lookup[ord];
}

static inline char base64char0(const uint8_t byte0) {
  return base64char(byte0 >> 2);
}

static inline char base64char1(const uint8_t byte0, const uint8_t byte1) {
  return base64char(((byte0 & 0x03) << 4) | (byte1 >> 4));
}

static inline char base64char2(const uint8_t byte1, const uint8_t byte2) {
  return base64char(((byte1 & 0x0F) << 2) | (byte2 >> 6));
}

static inline char base64char3(const uint8_t byte2) {
  return base64char(byte2 & 0x3F);
}

void bintobase64(const uint8_t * restrict bin, const size_t size,
                 char * restrict base64) {
  const size_t top = size - (size % 3);
  for (size_t i = 0; i < top; i += 3) {
    *base64++ = base64char0(bin[i]);
    *base64++ = base64char1(bin[i], bin[i+1]);
    *base64++ = base64char2(bin[i+1], bin[i+2]);
    *base64++ = base64char3(bin[i+2]);
  }

  if (size % 3 == 1) {
     *base64++ = base64char0(bin[top]); 
     *base64++ = base64char1(bin[top], 0);
     *base64++ = '=';
     *base64++ = '=';
  } else if (size % 3 == 2) {
     *base64++ = base64char0(bin[top]);
     *base64++ = base64char1(bin[top], bin[top+1]);
     *base64++ = base64char2(bin[top+1], 0);
     *base64++ = '=';
  }

  *base64 = '\0';
}

