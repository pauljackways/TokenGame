/*File:   display.c  
# Author: Paul Jackways (pja117), Katelyn McCarthy Freeman (kmc313)
# Date:   18 Oct 2023
# Descr:  file contaning the display functionality of the game*/


#include "display.h"
#include "system.h"
#include "pio.h"

// Array of PIOs represening rows in the LED matrix
static const pio_t rows[] = {
    LEDMAT_ROW1_PIO, LEDMAT_ROW2_PIO, LEDMAT_ROW3_PIO, 
    LEDMAT_ROW4_PIO, LEDMAT_ROW5_PIO, LEDMAT_ROW6_PIO,
    LEDMAT_ROW7_PIO
};

// Array of PIOs representing columns in the LED matrix
static pio_t cols[] = {
    LEDMAT_COL1_PIO, LEDMAT_COL2_PIO, LEDMAT_COL3_PIO,
    LEDMAT_COL4_PIO, LEDMAT_COL5_PIO
};

// Initialition function for the display
void display_init (void) {

    for (uint8_t i=0; i<7; i++) {
        pio_config_set (rows[i],PIO_OUTPUT_HIGH);
    }
    for (uint8_t i=0; i<5; i++) {
        pio_config_set (cols[i], PIO_OUTPUT_HIGH);
    }
}

// variable to keep track of the current row
uint8_t current_row = 0;

// Function to display a column in the LED matrix
void display_column(uint8_t row_pattern, uint8_t current_column)
{
    for (uint8_t i=0; i<LEDMAT_ROWS_NUM; i++) {
        pio_output_high (rows[i]);
    }
    pio_output_low(cols[current_column]);
    for (uint8_t i=0; i<7; i++) {
        current_row = i;
        if ((row_pattern >> i) & 1) {
            pio_output_low (rows[i]);
        } else {
            pio_output_high (rows[i]);
        }
    }
    pio_output_high(cols[current_column]);
}

// Combine two images and return the result
uint8_t display_add (uint8_t image_1, uint8_t image_2) 
{
    uint8_t result = image_2 | image_1;
    return result;
}