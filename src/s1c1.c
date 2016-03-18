#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "hex.h"
#include "base64.h"
#include "s1c1.h"

void hextobase64(const char * restrict hex, char * restrict base64) {
  uint8_t buf[strlen(hex)];
  const size_t size = hextobin(hex, buf);
  bintobase64(buf, size, base64);
}

int main() {
  const char *hex = "49276d20" "6b696c6c" "696e6720" "796f7572"
                    "20627261" "696e206c" "696b6520" "6120706f"
                    "69736f6e" "6f757320" "6d757368" "726f6f6d";
  char base64[strlen(hex)*2];
  hextobase64(hex, base64);
  puts(base64);
}
