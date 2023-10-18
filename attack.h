/*File:   attack.h 
# Author: Paul Jackways (pja117), Katelyn McCarthy Freeman (kmc313)
# Date:   18 Oct 2023
# Descr:  header file for attack.c*/


#ifndef ATTACK_H
#define ATTACK_H

#include <stdbool.h>
#include <stdint.h>

typedef enum  {
    LIGHTNING,
    SWORD,
    BAMBOOZ,
    NUKE, 
    NUM_SYMBOLS
} Symbols_enum;

bool attack_check(void);
void attack_switch(char attack);
void attack_lightning(void);
void attack_sword(void);
void attack_bambooz(void);
void attack_nuke(void);
uint8_t attack_choose(void);
void attack_init(void);

#endif
