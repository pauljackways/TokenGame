#include "totem_nav.h"
#include "system.h"
#include "navswitch.h"

// #define NAVSWITCH_NUM ARRAY_SIZE(navswitch_cfg)


// typedef struct
// {
//     bool current;
//     bool previous;
// } navswitch_state_t;

// /* Define navswitch PIO connections.  */    
// static const navswitch_cfg_t navswitch_cfg[] =
// {
//     {NAVSWITCH_NORTH_PIO},
//     {NAVSWITCH_EAST_PIO},
//     {NAVSWITCH_SOUTH_PIO}, 
//     {NAVSWITCH_WEST_PIO},
//     {NAVSWITCH_PUSH_PIO}
// };

// static navswitch_state_t navswitch_state[NAVSWITCH_NUM];

void totem_nav_init(void) {
    navswitch_init ();
}

bool totem_nav_response (void) {
    navswitch_update();
    if (navswitch_push_event_p (NAVSWITCH_NORTH) || \
    navswitch_push_event_p (NAVSWITCH_EAST) || \
    navswitch_push_event_p (NAVSWITCH_SOUTH) || \
    navswitch_push_event_p (NAVSWITCH_WEST) || \
    navswitch_push_event_p (NAVSWITCH_PUSH)) {
        return true;
    } else {
        return false;
    }
}

bool totem_nav_correct (uint8_t answer) {
    if (navswitch_down_p (answer)){
        return true;
    } else {
        return false;
    }
} 