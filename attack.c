#include "attack.h"
#include "display.h"
#include "pacer.h"
#include "ir_uart.h"
#include <stdbool.h>
#include <stdlib.h>

#define ATTACK_TIME 2 //s 
#define PACER_FREQ 750 //hz

bool attack_check(void) {
    char attack;
    // if (ir_uart_read_ready_p ())
    //     {
	//     attack = (ir_uart_getc ());
    //     }
    // convert ABC... to 012... ensures within range if there is interference
    // attack %= 10;
    // attack %= 4; // is there a macro for this?
    attack = 2;
    attack_switch(attack);
    return true;
}

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
        
        if (loop_count < iterations/4) {
            display_column (0xFF, current_column);
        } else if (loop_count % 2 == 0) {
            display_column(nuke[current_column],current_column);
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


void attack_choose(void) {

}