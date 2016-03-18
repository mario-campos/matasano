#pragma once

#include <stddef.h>
#include <stdint.h>

size_t hextobin(const char * restrict hex, uint8_t * restrict bin);

void bintohex(const uint8_t * restrict bin, const size_t size,
              char * restrict hex);
