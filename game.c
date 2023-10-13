#define TOTEM 5

#include "system.h"
#include "button.h"
#include "led.h"
#include "attack.h"
#include "startup.h"
#include "spin.h"



int main (void)
{
    system_init ();
    led_init ();
    button_init ();

    // Game initialisation - life bar animation?
    uint8_t led_level = 0;
    uint8_t totem_count = 0;
    bool button_on = false;

    while (1)
    {
        if (totem_count < led_level) {
            led_on ();
        } else {
            led_off ();
        }
        if (button_pressed_p () && button_on == false)
        {
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
    }
}