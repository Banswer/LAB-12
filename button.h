#ifndef BUTTON_H
#define BUTTON_H

#include <xc.h>
#include <stdbool.h>
#include "clock.h"
typedef enum {
    EVENT_IDLE,
    EVENT_PRESSED,
    EVENT_HELD
} event_t;

typedef enum {
    STATE_UNPRESSED,
    STATE_PRESSED
} btnState_t;

typedef struct {
    volatile uint8_t* port;
    uint8_t pin;
    btnState_t state;
    btnState_t lastState;
    event_t event;
    time_t timePressed;
} button_t;

extern button_t *up, *down, *enter, *menu;
bool BUTTONS_isClicked(button_t* button);
void BUTTONS_init() ;
void BUTTONS_task();
bool BUTTONS_isHeld(button_t* button);

#endif // BUTTON_H