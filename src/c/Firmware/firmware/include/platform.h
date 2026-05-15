#ifndef PLATFORM_H
#define PLATFORM_H

#include <stdint.h>

/* Global platform subsystem boundary interfaces */
void platform_init(void);
uint8_t *platform_get_test_binary_address(void);

#endif /* PLATFORM_H */

