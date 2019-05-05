#ifndef TM1650_H
#define	TM1650_H

#include<stdint.h>
#include<stdbool.h>

void TM1650_init();
void TM1650_setDigit(uint8_t digit, uint8_t data);
void TM1650_fastPrintNum(uint16_t num);
void TM1650_enable(bool enable);
bool TM1650_isEnabled();

#endif