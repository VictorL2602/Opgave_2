#define F_CPU 16000000UL
#include <avr/delay.h>
#include <avr/io.h>

char check_switch(void)
{
    static unsigned char last = 1;   // pull-up: 1 = ikke trykket
    unsigned char now = (PINE & (1<<PE4)) ? 1 : 0;

    if (last == 1 && now == 0) {
        _delay_ms(30); // debounce
        if ((PINE & (1<<PE4)) == 0) {
            last = 0;
            return 1;   // ét tryk registreret
        }
    }

    if (now == 1)
        last = 1;

    return 0;
}