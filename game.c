#define TOTEM 5
#define MAX_HEALTH 5
// MAX_HEALTH should not be changed until a formula has beed added to reduce the health bars to scale

#include "system.h"
#include "button.h"
#include "led.h"
#include "attack.h"
#include "startup.h"
#include "spin.h"
#include "display.h"
#include "pio.h"
#include <stdlib.h>

static uint8_t totem[LEDMAT_COLS_NUM];
static uint8_t healthbar[] =
{
    0x01, 0x01, 0x01, 0x01, 0x01
};

uint8_t damage (uint8_t health) 
{
    healthbar[health-1]--;
    return health - 1;
}

void get_totem (void) {
    const uint8_t totem_list[5][5] = {
        {0x10, 0x08, 0x7C, 0x08, 0x10},
        {0x10, 0x20, 0x7C, 0x20, 0x10},
        {0x10, 0x38, 0x54, 0x10, 0x10},
        {0x10, 0x10, 0x54, 0x38, 0x10},
        {0x10, 0x10, 0x7C, 0x10, 0x10}
    };
    uint8_t rand_i = rand() % 5;
    for (uint8_t i=0; i<LEDMAT_COLS_NUM; i++) {
        totem[i] = totem_list[rand_i][i];
    }
}

int main (void)
{
    system_init ();
    led_init ();
    button_init ();
    display_init();

    // Game initialisation - life bar animation?
    // startup();
    uint8_t led_level = 0;
    uint8_t totem_count = 0;
    bool button_on = false;
    uint8_t current_column = 0;
    uint8_t health = MAX_HEALTH;

    while (health >= 1)
    {
        display_column (display_add(totem[current_column],healthbar[current_column]), current_column);

        if (totem_count < led_level) {
            led_on ();
        } else {
            led_off ();
        }

        if (button_pressed_p () && button_on == false)
        {
            get_totem();
            health = damage(health);
            button_on = true;
            led_level++;
            if (led_level > TOTEM) {
                led_level = 0;
            }
        }
        if (!button_pressed_p ())
        {
            button_on = false;
        }
        // display an arrow (flag)
        // check for button press
            // if success: 
                // encourage the player
                // increment light
            // if failure:
                // you suck
                // reset light
            // if light greater than light macro:
                // run spin module (light flashes)
                // set light to 0
        // check for attack
            // if attacked: run attack module.  
            // decrease life bar
            // if life bar 0:
                // run ending module
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