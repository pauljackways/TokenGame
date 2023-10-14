#include "display.h"
#include "system.h"
#include "pio.h"

static const pio_t rows[] = {
    LEDMAT_ROW1_PIO, LEDMAT_ROW2_PIO, LEDMAT_ROW3_PIO, 
    LEDMAT_ROW4_PIO, LEDMAT_ROW5_PIO, LEDMAT_ROW6_PIO,
    LEDMAT_ROW7_PIO
};

static pio_t cols[] = {
    LEDMAT_COL1_PIO, LEDMAT_COL2_PIO, LEDMAT_COL3_PIO,
    LEDMAT_COL4_PIO, LEDMAT_COL5_PIO
};

void display_init (void) {

    for (uint8_t i=0; i<7; i++) {
        pio_config_set (rows[i],PIO_OUTPUT_HIGH);
    }
    for (uint8_t i=0; i<5; i++) {
        pio_config_set (cols[i], PIO_OUTPUT_HIGH);
    }
}

uint8_t current_row = 0;

void display_column(uint8_t row_pattern, uint8_t current_column)
{
    for (uint8_t i=0; i<LEDMAT_ROWS_NUM; i++) {
        pio_output_high (rows[i]);
    }
    pio_output_low(cols[current_column]);
    for (uint8_t i=0; i<8; i++) {
        current_row = i;
        if ((row_pattern >> i) & 1) {
            pio_output_low (rows[i]);
        } else {
            pio_output_high (rows[i]);
        }
    }
    pio_output_high(cols[current_column]);
}

uint8_t display_add (uint8_t image_1, uint8_t image_2) 
{
    uint8_t result = image_2 | image_1;
    return result;
}