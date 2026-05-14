#ifndef PLATFORM_H
#define PLATFORM_H

#include <stdint.h>

void platform_init(void);
uintptr_t platform_uart_base(void);

#endif
