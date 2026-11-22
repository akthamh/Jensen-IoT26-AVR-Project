#ifndef BUTTON_H
#define BUTTON_H

#include <stdbool.h>

typedef struct
{
    bool green_pressed;
    bool red_pressed;
    bool blue_pressed;
    bool gray_pressed;
    bool black_pressed;
}button_t;


void button_init();
void read_buttons(button_t *buttons);
void reset_buttons(button_t *buttons);

#endif