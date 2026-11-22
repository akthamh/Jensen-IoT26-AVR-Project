#include <util/delay.h>
#include <stdbool.h>

#include "app.h"
#include "config.h"
#include "gpio.h"
#include "pins.h"
#include "millis.h"
#include "spi.h"
#include "74hc595.h"
#include "keypad.h"
#include "led.h"
#include "button.h"

#define TOGGLE_TIME_MS 1000

void example_run(){

    // registers varibles
    shift_register_t register_A = {0, PD7, &DDRD, &PORTD, true};
    shift_register_t register_B = {0, PD6, &DDRD, &PORTD, true};
    shift_register_t register_C = {0, PD5, &DDRD, &PORTD, true};
    shift_register_t register_buffer = {0, PD4, &DDRD, &PORTD, true};
    shift_register_t keypad_and_rgb  = {0, PC5, &DDRC, &PORTC, false};
    shift_register_t *yellow_overflow = &keypad_and_rgb;
    
    // init
    millis_init();
    spi_init();

    shift_register_init(&register_A);
    shift_register_init(&register_B);
    shift_register_init(&register_C);
    shift_register_init(&register_buffer);
    shift_register_init(&keypad_and_rgb);

    keypad_init(&keypad_and_rgb);
    
    // init indiviual led
    init_led(yellow_overflow);
    gpio_pin_output(&REGISTER_A_LED_DDR, REGISTER_A_LED_PIN);
    gpio_pin_output(&REGISTER_B_LED_DDR, REGISTER_B_LED_PIN);


    millis_t last_toggle_time = millis_get();
    bool led_toggle_on = true;
    yellow_led_on();
    gpio_pin_high(&REGISTER_A_LED_PORT, REGISTER_A_LED_PIN);
    gpio_pin_high(&REGISTER_B_LED_PORT, REGISTER_B_LED_PIN);

    //rgb led functions array
    void (*rgb_led_colors_func[7])() = {rgb_red_led_on, rgb_green_led_on, rgb_blue_led_on, rgb_magenta_led_on, rgb_cyan_led_on, rgb_yellow_led_on, rgb_white_led_on};
    const uint8_t rgb_led_colors_count = 7;
    uint8_t rgb_led_colors_selected = 0;
    rgb_led_colors_func[rgb_led_colors_selected]();

    //button init
    button_init();
    button_t buttons;
    reset_buttons(&buttons);

    //tests
    shift_register_write(&register_A, 10);
    shift_register_write(&register_B, 23);
    shift_register_write(&register_C, 88);
    shift_register_write(&register_buffer, 177);


    while (1){
        char key;

        key = keypad_get_key_debounced();
        uint8_t update_bit = 255;
        if (key!=0){
            switch (key)
            {
            case '0':
                update_bit = 0;
                break;
                                
            case '1':
                /* code */
                update_bit = 1;
                break;
            case '2':
                /* code */
                update_bit = 2;

                break;
                                
            case '3':
                /* code */
                update_bit = 3;

                break;    
            case '4':
                /* code */
                update_bit = 4;

                break;
                                
            case '5':
                /* code */
                update_bit = 5;

                break;
            case '6':
                /* code */
                update_bit = 6;

                break;
                                
            case '7':
                /* code */
                update_bit = 7;

                break;                                
            case '8':
                /* code */
                update_bit = 8;

                break;
                                
            case '9':
                /* code */
                update_bit = 9;

                break;
            case 'A':
                update_bit = 10;

                /* code */
                break;
                                
            case 'B':
                update_bit = 11;

                /* code */
                break; 
            case 'C':
                update_bit = 12;

                /* code */
                break;
                                
            case 'D':
                update_bit = 13;

                /* code */
                break;
            case 'E':
                update_bit = 14;

                /* code */
                break;
                                
            case 'F':
                update_bit = 15;

                /* code */
                break;                       
            default:
                update_bit = 255;
                break;
            }
            shift_register_write(&register_A, update_bit);
            shift_register_write(&register_B, update_bit);
            shift_register_write(&register_C, update_bit);
            shift_register_write(&register_buffer, update_bit);                  
        }

        if((millis_get() - last_toggle_time) > TOGGLE_TIME_MS){
            if(led_toggle_on){
                yellow_led_off();
                gpio_pin_low(&REGISTER_A_LED_PORT, REGISTER_A_LED_PIN);
                gpio_pin_low(&REGISTER_B_LED_PORT, REGISTER_B_LED_PIN);
            }
            else{
                yellow_led_on();
                gpio_pin_high(&REGISTER_A_LED_PORT, REGISTER_A_LED_PIN);
                gpio_pin_high(&REGISTER_B_LED_PORT, REGISTER_B_LED_PIN);
            }

            rgb_led_colors_selected++;
            rgb_led_colors_selected = rgb_led_colors_selected % rgb_led_colors_count;
            rgb_led_colors_func[rgb_led_colors_selected]();

            led_toggle_on = !led_toggle_on;
            last_toggle_time = millis_get();
        }

        // read buttons
        reset_buttons(&buttons);
        read_buttons(&buttons);

        if(buttons.green_pressed){
            shift_register_write(&register_C, 255);
        }
        if(buttons.red_pressed){
            shift_register_write(&register_A, 255);
        }
        if(buttons.blue_pressed){
            shift_register_write(&register_B, 255);
        }
        if(buttons.gray_pressed){
            shift_register_write(&register_buffer, 255);
        }
        if(buttons.black_pressed){
            shift_register_write(&register_A, 240);
            shift_register_write(&register_B, 240);
            shift_register_write(&register_C, 240);
            shift_register_write(&register_buffer, 240);
        }

    }
}

void app_run(void)
{   
    // remove example function when implementing real program
    example_run();

    // TODO, make program here!
}