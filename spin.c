#include "spin.h"
#include "button.h"
#include "system.h"
#include "led.h"
#include "timer.h"
#include "pio.h"
#include "navswitch.h"
#include "font.h"
#include "tinygl.h"
#include "pacer.h"

#define LOOP_RATE 1000
#define LED_RATE 2


int flash (void)
{
    unsigned int count = 0;
    unsigned int period = LOOP_RATE / LED_RATE;

    system_init ();
    timer_init ();
    pio_config_set (LED1_PIO, PIO_OUTPUT_HIGH);

    while (1)
    {
        timer_wait (TIMER_RATE / LOOP_RATE);
        pio_output_set (LED1_PIO, count < period / 2);
        count++;
        if (count >= period)
            count = 0;
    }

    return 0;
}

#define LOOP_RATE 300
#define MESSAGE_RATE 10

int spin (void)
{
    system_init ();
    tinygl_init (LOOP_RATE);
    tinygl_font_set (&font5x7_1);
    tinygl_text_speed_set (MESSAGE_RATE);
    tinygl_text_mode_set (TINYGL_TEXT_MODE_SCROLL);
    tinygl_text ("HELLO WORLD");
    pacer_init (LOOP_RATE);
    button_init ();

 
    bool scroll_enabled = true;
    char most_visible_char = 'H';

    while (1)
    {
    
        if (navswitch_push_event_p (BUTTON1))
        {
            scroll_enabled = !scroll_enabled;
        }

        if (scroll_enabled)
        {
            tinygl_update ();
        }
        else
        {
            tinygl_draw_char (most_visible_char);
            tinygl_update ();
        }

        int8_t x = tinygl_point ();
        if (x >= 0)
        {
            int8_t char_position = x / (TINYGL_FONT_WIDTH + 1);
            most_visible_char = "HELLO WORLD"[char_position];
        }

        pacer_wait ();
    }

    return 0;
}

#include "system.h"
#include "navswitch.h"
#include "tinygl.h"
#include "pacer.h"
#include "../fonts/font5x7_1.h"


/* Define polling rate in Hz.  */
#define LOOP_RATE 300

/* Define text update rate (characters per 10 s).  */
#define MESSAGE_RATE 10


int main (void)
{
    system_init ();
    tinygl_init (LOOP_RATE);

    navswitch_init ();

    tinygl_font_set (&font5x7_1);
    tinygl_text_speed_set (MESSAGE_RATE);
    tinygl_text_mode_set (TINYGL_TEXT_MODE_SCROLL);

    tinygl_text ("HELLO WORLD");

    pacer_init (LOOP_RATE);

    /* Paced loop.  */
    while (1)
    {
        /* Wait for next tick.  */
        pacer_wait ();

        tinygl_update ();

        navswitch_update ();

        if (navswitch_push_event_p (NAVSWITCH_WEST))
            tinygl_text_mode_set (TINYGL_TEXT_MODE_STEP);

        if (navswitch_push_event_p (NAVSWITCH_EAST))
            tinygl_text_mode_set (TINYGL_TEXT_MODE_SCROLL);

    }

    return 0;
}
