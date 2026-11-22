#ifndef SHIFT_74hc595
#define SHIFT_74hc595

#include <avr/io.h>
#include <stdbool.h>

#define SHIFT_Q0 (1 << 0)
#define SHIFT_Q1 (1 << 1)
#define SHIFT_Q2 (1 << 2)
#define SHIFT_Q3 (1 << 3)
#define SHIFT_Q4 (1 << 4)
#define SHIFT_Q5 (1 << 5)
#define SHIFT_Q6 (1 << 6)
#define SHIFT_Q7 (1 << 7)

typedef struct
{
    uint8_t state;
    uint8_t pin;
    volatile uint8_t *ddr;
    volatile uint8_t *port;
    bool reverse;
}shift_register_t;


void shift_register_init(shift_register_t *sr);
void shift_register_write(shift_register_t *sr, uint8_t byte);
void shift_register_set_bits(shift_register_t *sr, uint8_t bits);
void shift_register_clear_bits(shift_register_t *sr, uint8_t bits);

#endif