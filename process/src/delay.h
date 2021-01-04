#ifndef _DELAY_H
#define _DELAY_H

#include <intrins.h>
void delay(unsigned int r);
void delay_min(unsigned int r);

#define NOP() _nop_()

#endif
