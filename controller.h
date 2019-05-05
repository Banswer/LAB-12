#ifndef CONTROLLER_H
#define	CONTROLLER_H

#include <xc.h> 
#include <stdint.h>

void CONTROLLER_init();
void address_inc();
void address_dec();
void CONTROLLER_task();

extern uint16_t address;
//LED_setColor(dmx[address+1], dmx[address+2])

#endif	
