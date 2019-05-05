/*
 * File:   controller.c
 * Author: Owner
 *
 * Created on April 17, 2019, 3:54 PM
 */


#include "controller.h"
#include "button.h"
#include "clock.h"
#include "tm1650.h"

uint16_t address = 1;

void CONTROLLER_init() {
    TM1650_fastPrintNum(address);
}

/**
 * Increments the address and updates the display
 */
void address_inc()
{
    if(address == 512)
        address = 1;
    else
        address++;
    
    // update the display
    TM1650_fastPrintNum(address);
}

/**
 * Decrements the address and updates the display
 */
void address_dec() 
{
    if(address == 1)
        address = 512;
    else
        address--;  
    
    // update the display
    TM1650_fastPrintNum(address);
}
static time_t lastTime = 0;

void CONTROLLER_task() {
        time_t time = CLOCK_getTime();

    // only run every 10 ms
    if (time - lastTime < 10)
        return;

  //  lastTime = time;
    bool active = true;
    
    if (BUTTONS_isClicked(up)) {
        address_inc();
        
    } else if (BUTTONS_isClicked(down)) {
        address_dec();
    } else if (BUTTONS_isHeld(up)) {
        address_inc();
        
    } else if (BUTTONS_isHeld(down)) {
        address_dec();
    } else {
        active = false;
    }
    
    if(active)
    {
        TM1650_enable(true);
        lastTime = CLOCK_getTime();
    }
    
    if(CLOCK_getTime() - lastTime >= 5000)
    {
        TM1650_enable(false);
        lastTime = CLOCK_getTime() - 5001;
    }

}
