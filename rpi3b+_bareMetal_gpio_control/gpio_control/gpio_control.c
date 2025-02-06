// gpio_control.c - C Code
#include <stdint.h>

#define GPFSEL1 0x3F200004
#define GPSET0  0x3F20001C

volatile unsigned int *gpio_fsel1 = (unsigned int *)GPFSEL1;
volatile unsigned int *gpio_set0 = (unsigned int *)GPSET0;

void main()
{
    *gpio_fsel1 |= (1 << 21); 	   // Configure GPIO 17 as output
    *gpio_set0 = (1 << 17);  	   // Turn on LED
    for(;;) {}                     // Infinite loop
}

