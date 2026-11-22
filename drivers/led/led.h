#ifndef LED_H_
#define LED_H_

#include "74hc595.h"

void rgb_off();

void init_led(shift_register_t *sr);

void rgb_green_led_on();
void rgb_green_led_off();

void rgb_red_led_on();
void rgb_red_led_off();

void rgb_blue_led_on();
void rgb_blue_led_off();

void rgb_cyan_led_on();
void rgb_cyan_led_off();

void rgb_yellow_led_on();
void rgb_yellow_led_off();

void rgb_magenta_led_on();
void rgb_magenta_led_off();

void rgb_white_led_on();
void rgb_white_led_off();

void yellow_led_on();
void yellow_led_off();

#endif