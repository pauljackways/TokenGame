/*File:   game.c  
# Author: Paul Jackways (pja117), Katelyn McCarthy Freeman (kmc313)
# Date:   18 Oct 2023
# Descr:  file contaning the general functionality of the game*/

#define TOTEM 10
#define MAX_HEALTH 5

#include "system.h"
#include "button.h"
#include "led.h"
#include "attack.h"
#include "startup.h"
#include "display.h"
#include "pio.h"
#include "totem_nav.h"
#include <stdlib.h>

// Set health bar lights to full 
static uint8_t totem[LEDMAT_COLS_NUM];
static uint8_t healthbar[] =
{
    0x01, 0x01, 0x01, 0x01, 0x01
};

static uint8_t health = MAX_HEALTH;

// Update health bar when attacked
void damage(void) 
{
    if (health % (MAX_HEALTH / LEDMAT_COLS_NUM) == 0) {
        healthbar[(health-1) / (MAX_HEALTH / LEDMAT_COLS_NUM)]--;
    }
    health--;
}

// Get random totem
uint8_t get_totem (uint8_t current_totem) {
    const uint8_t totem_list[5][5] = {
        {0x10, 0x08, 0x7C, 0x08, 0x10},
        {0x10, 0x10, 0x54, 0x38, 0x10},
        {0x10, 0x20, 0x7C, 0x20, 0x10},
        {0x10, 0x38, 0x54, 0x10, 0x10},
        {0x10, 0x10, 0x7C, 0x10, 0x10}
    };
    uint8_t rand_i = rand() % LEDMAT_COLS_NUM;
    while (rand_i == current_totem) {
        rand_i = rand() % LEDMAT_COLS_NUM;
    }
    for (uint8_t i=0; i<LEDMAT_COLS_NUM; i++) {
        totem[i] = totem_list[rand_i][i];
    }
    return rand_i;
}

int main (void)
{
    system_init ();
    led_init ();
    button_init ();
    display_init();
    totem_nav_init();
    attack_init();
    uint8_t current_column = 0;
    const uint8_t push_button[5] = // Push button symbol
        {2, 68, 111, 68, 2};
    while (!button_pressed_p()) {
        display_column (push_button[current_column], current_column);
        current_column++;
        if (current_column > (LEDMAT_COLS_NUM - 1))
        {
            current_column = 0;
        }   
    }

    // Game initialisation 
    uint8_t led_level = 0;
    uint8_t totem_count = 0;
    bool button_on = false;
    uint8_t correct = get_totem(-1);
    uint8_t attack_choose_damage; // Damage taken while in attack_choose()
    current_column = 0;
    while (health >= 1)
    {
        // Display an arrow (flag)
        display_column (display_add(totem[current_column],healthbar[current_column]), current_column);

        // Keep track of progress with LED level
        if (totem_count < led_level) {
            led_on ();
        } else {
            led_off ();
        }
        // Check for attack
        if (attack_check()) {
            damage();
        }

        // Check for button press
        if (totem_nav_response()) {
            if (totem_nav_correct(correct)) {
                led_level++;
                if (led_level > TOTEM) {
                    led_level = 0;
                    attack_choose_damage = attack_choose(); 
                    for (uint8_t i=0; i<attack_choose_damage; i++) {
                        damage();
                    }
                }
                correct = get_totem(correct);
            } else {
                led_level = 0; // Restart
            }
        }
        
        // Check for button press
        if (button_pressed_p () && button_on == false)
        {
            button_on = true;
            
        }
        if (!button_pressed_p ())
        {
            button_on = false;
        }
        
        // Reset for next round
        totem_count++;
        if (totem_count >= TOTEM) {
            totem_count = 0;
        }
        
        current_column++;
        if (current_column > (LEDMAT_COLS_NUM - 1))
        {
            current_column = 0;
        }     
    }
    // GAME OVER
}
