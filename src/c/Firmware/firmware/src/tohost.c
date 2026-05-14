#include "tohost.h"

volatile unsigned int tohost;

void tohost_set_pass(uint32_t code) { tohost = (code << 1) | 1u; }

void tohost_set_fail(uint32_t code) { tohost = (code << 1); }
