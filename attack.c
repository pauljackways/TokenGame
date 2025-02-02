/*File:   attack.c  
# Author: Paul Jackways (pja117), Katelyn McCarthy Freeman (kmc313)
# Date:   18 Oct 2023
# Descr:  file contaning the attack functions of the game*/

#include "attack.h"
#include "display.h"
#include "pacer.h"
#include "ir_uart.h"
#include <stdbool.h>
#include <stdlib.h>
#include "system.h"
#include "pio.h"
#include "navswitch.h"
#include "button.h"
#include "led.h"

#define ATTACK_TIME 2 //s 
#define PACER_FREQ 750 //hzs
// Note: There are exactly 4 attacks

// initialise connection
void attack_init(void) {
    ir_uart_init();
}

// Checks for attacks. Runs attack animation, then returns true if attacked
bool attack_check(void) {
    char attack = 0;
    if (ir_uart_read_ready_p ()) {
	    attack = ir_uart_getc ();
        // convert ABC... to 012... ensures within range if there is interference
        attack %= 10;
        attack %= NUM_SYMBOLS; // number of attacks
        attack_switch(attack);
        return true;
        }
    return false;
}

// Simple switch, breaks attack animations into separate functions
void attack_switch(char attack) {
    switch(attack) {
        case 0:
            attack_lightning();
            break;
        case 1:
            attack_sword();
            break;
        case 2:
            attack_bambooz();
            break;
        case 3:
            attack_nuke();
            break;
    }
}

// lightning attack - flashing
void attack_lightning() {
    pacer_init (PACER_FREQ);
    uint16_t loop_count = 0; 
    uint8_t current_column = 0;
    uint16_t iterations = ATTACK_TIME*PACER_FREQ;
    while(loop_count < iterations) { // how many loops in ATTACK_TIME s, accounting for columns
        
        if (loop_count % 50 < 25) {
            display_column (0xFF, current_column);
        }
        if (loop_count % 50 >= 25) {
            display_column (0x00, current_column);
        }
        current_column++;
        if (current_column > (LEDMAT_COLS_NUM - 1))
        {
            current_column = 0;
        }   
        pacer_wait ();
        loop_count++;
    }
}

// sword attack - cut in half
void attack_sword() {
    pacer_init (PACER_FREQ);
    uint16_t loop_count = 0; 
    uint8_t current_column = 0;
    uint16_t iterations = ATTACK_TIME*PACER_FREQ;
    const uint8_t frames[7][5] = {
        {0x60, 0x30, 0x18, 0x0C, 0x06},
        {79, 103, 115, 121, 124},
        {0xFF, 0xFF, 0xFF, 0xFF, 124},
        {0xFF, 0xFF, 0xFF, 120, 124},
        {0xFF, 0xFF, 112, 120, 124},
        {0xFF, 96, 112, 120, 124},
        {64, 96, 112, 120, 124}
    };
    uint16_t frame = iterations/30;
    while(loop_count < iterations) { // how many loops in ATTACK_TIME s, accounting for columns
        if (loop_count < 2*frame) {
            display_column (0xFF, current_column);
        }
        if (loop_count > 2*frame && loop_count < 3*frame) {
            display_column (frames[0][current_column], current_column);
        }
        if (loop_count > 3*frame && loop_count < 4*frame) {
            display_column (0xFF, current_column);
        }
        if (loop_count > 4*frame && loop_count < 5*frame) {
            display_column (frames[1][current_column], current_column);
        }
        if (loop_count > 5*frame && loop_count < 6*frame) {
            display_column (frames[2][current_column], current_column);
        }
        if (loop_count > 6*frame && loop_count < 7*frame) {
            display_column (frames[3][current_column], current_column);
        }
        if (loop_count > 7*frame && loop_count < 8*frame) {
            display_column (frames[4][current_column], current_column);
        }
        if (loop_count > 8*frame && loop_count < 9*frame) {
            display_column (frames[5][current_column], current_column);
        }
        if (loop_count > 9*frame) {
            display_column (frames[6][current_column], current_column);
        }
        current_column++;
        if (current_column > (LEDMAT_COLS_NUM - 1))
        {
            current_column = 0;
        }   
        pacer_wait ();
        loop_count++;
    }
}

// bambooz (confusion) attack - spiral
void attack_bambooz() {
    pacer_init (PACER_FREQ);
    uint16_t loop_count = 0; 
    uint8_t current_column = 0;
    uint16_t iterations = ATTACK_TIME*PACER_FREQ;
    const uint8_t bambooz[4][5] = {
    {126, 66, 90, 82, 94},
    {2, 58, 42, 34, 58},
    {61, 37, 45, 33, 63},
    {62, 34, 42, 46, 32}
    };
    uint16_t max_rate = 50;
    uint16_t rate = 0;
    uint8_t frame = 0;
    while(loop_count < iterations) { // how many loops in ATTACK_TIME s, accounting for columns
        
        if (rate == max_rate) {
            frame++;
            frame %= 4; //number of frames
            rate = 0;
        }

        display_column (bambooz[frame][current_column], current_column);

        current_column++;
        if (current_column > (LEDMAT_COLS_NUM - 1))
        {
            current_column = 0;
        }   
        pacer_wait ();
        rate++;
        loop_count++;
    }
}

// nuke attack - flash then explosion, with nuke symbol overlaid
void attack_nuke() {
    pacer_init (PACER_FREQ);
    uint16_t loop_count = 0; 
    uint8_t current_column = 0;
    uint16_t iterations = ATTACK_TIME*PACER_FREQ;
    uint8_t random;
    const uint8_t nuke[5] = {
        0x30, 0x22, 0x0A, 0x22, 0x30
    };
    while(loop_count < iterations) { // how many loops in ATTACK_TIME s, accounting for columns
        // flash and nuke symbol
        if (loop_count < iterations/4) {
            display_column (0xFF, current_column);
        } else if (loop_count % 2 == 0) {
            display_column(nuke[current_column],current_column);
        // Explosion - random static that fades out
        } else if (loop_count % 2 == 1) {
            random = rand() % 127;
            if (loop_count > iterations/4 && loop_count < iterations/2) {
                display_column(random,current_column);
            } else if (loop_count % 8 == 1 && loop_count > iterations/2 && loop_count < 3*iterations/4){
                display_column(random,current_column);
            } else if (loop_count % 32 == 1) {
                display_column(random,current_column);
            }
        }
        current_column++;
        if (current_column > (LEDMAT_COLS_NUM - 1))
        {
            current_column = 0;
        }   
        pacer_wait ();
        loop_count++;
    }
}


// Bitmaps for the selection symbols
static const uint8_t symbols[4][5] = {
    {0x00, 0x44, 0x2A, 0x11, 0x00},
    {0x0A, 0x04, 0x0A, 0x10, 0x20},
    {0x78, 0x48, 0x4D, 0x40, 0x60},
    {0x30, 0x22, 0x0A, 0x22, 0x30}
};

// 
uint8_t attack_choose(void) {
    uint8_t current_column = 0;
    Symbols_enum symbol_index = rand() % NUM_SYMBOLS; // Start with a random symbol.

    bool is_led_on = false;
    uint16_t led_flash_interval = 500; // Adjust the flashing interval as needed
    uint16_t led_flash_counter = 0;
    int chooser = 0;
    uint8_t attack_count = 0;
    while (chooser == 0) {
        attack_count += attack_check();
        // Handle NavSwitch input
        navswitch_update();
        if (navswitch_push_event_p(NAVSWITCH_EAST)) {
            // Cycle to the next symbol
            symbol_index = (symbol_index + 1) % NUM_SYMBOLS;
        }
        if (navswitch_push_event_p(NAVSWITCH_WEST)) {
            // Cycle to the next symbol
            symbol_index = (symbol_index - 1) % NUM_SYMBOLS;
        }
        display_column(symbols[symbol_index][current_column], current_column);
        current_column++;

        if (current_column >= LEDMAT_COLS_NUM) {
            current_column = 0;
        }

        if (led_flash_counter >= led_flash_interval) {
            is_led_on = !is_led_on;
            if (is_led_on) {
                led_on (); // Turn on the LED
            } else {
                led_off ();  // Turn off the LED
            }
            led_flash_counter = 0;
        }
        led_flash_counter++;


        if (button_pressed_p()) {
            ir_uart_putc(symbol_index + 10); // 0 -> 10 to avoid possible interference when sending 0
            chooser = 1;
        }
    }
    return attack_count;
}
