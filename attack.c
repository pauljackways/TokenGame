#include "attack.h"
#include "display.h"
#include "pacer.h"
#include "ir_uart.h"
#include <stdbool.h>

#define ATTACK_TIME 3 //s 
#define PACER_FREQ 5000 //hz

bool attack_check(void) {
    char attack;
    // if (ir_uart_read_ready_p ())
    //     {
	//     attack = (ir_uart_getc ());
    //     }
    // convert ABC... to 012... ensures within range if there is interference
    // attack %= 10;
    // attack %= 4; // is there a macro for this?
    attack = 0;
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
            attack_cinder();
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
        
        if (loop_count % 500 < 250) {
            display_column (0xFF, current_column);
        }
        if (loop_count % 500 >= 250) {
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
    
}

void attack_cinder() {
    
}

void attack_nuke() {
    pacer_init (PACER_FREQ);
    uint16_t loop_count = 0; 
    uint8_t current_column = 0;
    uint16_t iterations = ATTACK_TIME*PACER_FREQ;
    while(loop_count < iterations) { // how many loops in ATTACK_TIME s, accounting for columns
        
        if (loop_count < iterations/3) {
            display_column (0xFF, current_column);
        }
        if (loop_count > iterations/3) {
            
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