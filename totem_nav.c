#include "totem_nav.h"
#include "system.h"
#include "navswitch.h"

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
