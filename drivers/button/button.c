#include <avr/io.h>
#include <util/delay.h>
#include "button.h"

#define BUTTONS (1 << DDC0) | (1 << DDC1) | (1 << DDC2) | (1 << DDC3) | (1 << DDC4)

void button_init(){
    DDRC  &= ~0x1F;   // PC0–PC4 as inputs
    PORTC |=  0x1F;   // pull-ups on all four

    // Make sure the digital input buffer is not disabled (only matters if the ADC was used)
    DIDR0 &= ~(1 << ADC0D);
}
void reset_buttons(button_t *buttons){
    buttons -> green_pressed = false;
    buttons -> red_pressed = false;
    buttons -> blue_pressed = false;
    buttons -> gray_pressed = false;
    buttons -> black_pressed = false;
}

void read_buttons(button_t *buttons){
    if(~PINC & 0x1F){
        _delay_ms(20);
        uint8_t button_state = ~PINC & 0x1F;
        if(button_state){
            // at least one button is pressed
            buttons -> green_pressed = (button_state & (1 << PINC0))?true:false;
            buttons -> red_pressed = (button_state & (1 << PINC1))?true:false;
            buttons -> blue_pressed = (button_state & (1 << PINC2))?true:false;
            buttons -> gray_pressed = (button_state & (1 << PINC3))?true:false;
            buttons -> black_pressed = (button_state & (1 << PINC4))?true:false;
        }
    }
}