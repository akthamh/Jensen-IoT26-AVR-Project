#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>
#include "74hc595.h"

#define ROW1 SHIFT_Q0
#define ROW2 SHIFT_Q1
#define ROW3 SHIFT_Q2
#define ROW4 SHIFT_Q3

/*
    4x4 keypad

    Layout:
    1 2 3 A
    4 5 6 B
    7 8 9 C
    F 0 E D
*/
static shift_register_t *keypad_sr;

static const char keypad_map[4][4] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'F', '0', 'E', 'D'}
};

void keypad_init(shift_register_t *sr)
{
    keypad_sr = sr;
    /* PD4-PD7 som ingångar */
    DDRD &= ~(1 << PD3) | (1 << PD2) | (1 << PD1) | (1 << PD0);

    /* Aktivera pull-up på kolumner */
    PORTD |= (1 << PD3) | (1 << PD2) | (1 << PD1) | (1 << PD0);
}

static void keypad_set_all_rows_high(void)
{
    shift_register_set_bits(keypad_sr, ROW1 | ROW2 | ROW3 | ROW4);
}

static void keypad_set_row_low(uint8_t row)
{
    keypad_set_all_rows_high();

    switch (row)
    {
        case 0:
            shift_register_clear_bits(keypad_sr, ROW1);
            break;
        case 1:
            shift_register_clear_bits(keypad_sr, ROW2);
            break;
        case 2:
            shift_register_clear_bits(keypad_sr, ROW3);
            break;
        case 3:
            shift_register_clear_bits(keypad_sr, ROW4);
            break;
        default:
            break;
    }
}

static uint8_t keypad_read_column(void)
{
    if (!(PIND & (1 << PD3))) return 0;
    if (!(PIND & (1 << PD2))) return 1;
    if (!(PIND & (1 << PD1))) return 2;
    if (!(PIND & (1 << PD0))) return 3;

    return 0xFF;
}

char keypad_get_key(void)
{
    uint8_t row;
    uint8_t col;

    for (row = 0; row < 4; row++)
    {
        keypad_set_row_low(row);

        /* kort stabiliseringstid */
        _delay_us(5);

        col = keypad_read_column();
        if (col != 0xFF)
        {
            return keypad_map[row][col];
        }
    }

    return 0;
}

char keypad_get_key_debounced(void)
{
    char key = keypad_get_key();

    if (key != 0)
    {
        _delay_ms(20);

        if (key == keypad_get_key())
        {
            /* vänta tills knappen släpps */
            while (keypad_get_key() != 0)
            {
                _delay_ms(5);
            }

            return key;
        }
    }

    return 0;
}