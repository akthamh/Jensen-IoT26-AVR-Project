#include "74hc595.h"

#define RGB_BLUE SHIFT_Q7
#define RGB_GREEN SHIFT_Q6
#define RGB_RED SHIFT_Q5
#define YELLOW SHIFT_Q4

static shift_register_t *rgb_shift;

void rgb_off()
{
    shift_register_clear_bits(rgb_shift, RGB_BLUE | RGB_GREEN| RGB_RED);
}

void init_led(shift_register_t *sr)
{   
    rgb_shift = sr;
    rgb_off();
}

void yellow_led_on(){
    shift_register_set_bits(rgb_shift, YELLOW);
}

void yellow_led_off(){
    shift_register_clear_bits(rgb_shift, YELLOW);
}

void rgb_green_led_on()
{
    rgb_off();
    shift_register_set_bits(rgb_shift, RGB_GREEN);
}

void rgb_green_led_off()
{
    shift_register_set_bits(rgb_shift, RGB_GREEN);
}

void rgb_red_led_on()
{
    rgb_off();
    shift_register_set_bits(rgb_shift, RGB_RED);
}

void rgb_red_led_off()
{
    shift_register_clear_bits(rgb_shift, RGB_RED);
}

void rgb_blue_led_on()
{
    rgb_off();
    shift_register_set_bits(rgb_shift, RGB_BLUE);
}

void rgb_blue_led_off()
{
    shift_register_clear_bits(rgb_shift, RGB_BLUE);
}

void rgb_cyan_led_on()
{   
    rgb_off();
    shift_register_set_bits(rgb_shift, RGB_BLUE | RGB_GREEN);
}

void rgb_cyan_led_off()
{
    shift_register_clear_bits(rgb_shift, RGB_BLUE | RGB_GREEN);
}

void rgb_yellow_led_on()
{   
    rgb_off();
    shift_register_set_bits(rgb_shift, RGB_GREEN| RGB_RED);
}

void rgb_yellow_led_off()
{
    shift_register_clear_bits(rgb_shift, RGB_GREEN| RGB_RED);
}

void rgb_magenta_led_on()
{
    rgb_off();
    shift_register_set_bits(rgb_shift, RGB_BLUE | RGB_RED);
}

void rgb_magenta_led_off()
{
    shift_register_clear_bits(rgb_shift, RGB_BLUE | RGB_RED);
}

void rgb_white_led_on()
{
    shift_register_set_bits(rgb_shift, RGB_BLUE | RGB_GREEN| RGB_RED);
}

void rgb_white_led_off()
{
    shift_register_clear_bits(rgb_shift, RGB_BLUE | RGB_GREEN| RGB_RED);
}