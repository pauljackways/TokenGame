#define TOTEM 15
#define MAX_HEALTH 5

#include "system.h"
#include "button.h"
#include "led.h"
#include "attack.h"
#include "startup.h"
#include "spin.h"
#include "display.h"
#include "pio.h"

static uint8_t bitmap[] =
{
    0x01, 0x01, 0x01, 0x01, 0x01
};

uint8_t damage (uint8_t health) 
{
    bitmap[health-1]--;
    if (health == 1) {
    }
    return health - 1;
}

int main (void)
{
    system_init ();
    led_init ();
    button_init ();
    display_init();

    // Game initialisation - life bar animation?
    uint8_t led_level = 0;
    uint8_t totem_count = 0;
    bool button_on = false;
    
    // startup();

    uint8_t current_column = 0;
    uint8_t health = MAX_HEALTH;

    while (1)
    {
        display_column (bitmap[current_column], current_column);

        if (totem_count < led_level) {
            led_on ();
        } else {
            led_off ();
        }

        if (button_pressed_p () && button_on == false)
        {
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
}