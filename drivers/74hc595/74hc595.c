#include <avr/io.h>
#include <util/delay.h>
#include "74hc595.h"
#include "spi.h"

#define LATCH_PIN PD2
#define LATCH_PORT PORTD
#define LATCH_DDR DDRD

static uint8_t reverse(uint8_t b) {
    b = (b & 0xF0) >> 4 | (b & 0x0F) << 4;
    b = (b & 0xCC) >> 2 | (b & 0x33) << 2;
    b = (b & 0xAA) >> 1 | (b & 0x55) << 1;
    return b;
}

static void latch(shift_register_t *sr)
{
    (*sr->port) |= (1 << sr->pin);
    _delay_us(5);
    (*sr->port) &= ~(1 << sr->pin);
}

void shift_register_write(shift_register_t *sr, uint8_t byte){
    sr->state = (sr->reverse)?reverse(byte):byte;
    spi_transfer(sr->state);
    latch(sr);
}

void shift_register_set_bits(shift_register_t *sr, uint8_t bits)
{   
    sr->state |= (sr->reverse)?reverse(bits):bits;
    spi_transfer(sr->state);
    latch(sr);
}

void shift_register_clear_bits(shift_register_t *sr, uint8_t bits)
{
    sr->state &= ~((sr->reverse)?reverse(bits):bits);
    spi_transfer(sr->state);
    latch(sr);
}

void shift_register_init(shift_register_t *sr)
{   
    // set pin as output 
    (*sr->ddr)|=(1<< sr->pin);
    // set standard low
    (*sr->port) &= ~(1<< sr->pin);
    shift_register_write(sr, 0);
}