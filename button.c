#include "pio.h"
#include "button.h"
#define BTN1_PIO PIO_DEFINE (PORT_D, 7)

/** Return non-zero if button pressed.  */
int button_pressed_p (void)
{
    return pio_input_get (BTN1_PIO);
}


/** Initialise button1.  */
void button_init (void)
{
    pio_config_set (BTN1_PIO, PIO_INPUT);
}

