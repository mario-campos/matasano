#pragma once

#include <stddef.h>
#include <stdint.h>

size_t base64tobin(const char * restrict base64, uint8_t * restrict bin);

void bintobase64(const uint8_t * restrict bin, const size_t size,
                 char * restrict base64);
