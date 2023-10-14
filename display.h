#ifndef DISPLAY_H
#define DISPLAY_H

#include  <stdint.h>

void display_init (void);
void display_column(uint8_t row_pattern, uint8_t current_column);
uint8_t display_add (uint8_t image_1, uint8_t image_2); 


#endif