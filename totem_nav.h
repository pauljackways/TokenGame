#ifndef TOTEM_NAV_H
#define TOTEM_NAV_H

#include <stdbool.h>
#include <stdint.h>

void totem_nav_init(void);
bool totem_nav_response (void);
bool totem_nav_correct (uint8_t answer);

#endif
