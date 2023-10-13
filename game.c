#define TOTEM 5

#include "system.h"
#include "startup.h"
#include "spin.h"
#include "attack.h"
#include "button.h"
#include "led.h"

int main (void)
{
    system_init ();

    // Game initialisation - life bar animation?

    while (1)
    {
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
    }
}