#include "app.h"
#include <avr/interrupt.h>

int main(void)
{
    sei();

    while (1)
    {
        app_run();
    }
}