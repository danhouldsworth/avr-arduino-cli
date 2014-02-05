// main.c

// #include <avr/io.h>
// #include <util/delay.h>
// #include <stdint.h>
#include <Arduino.h>
// #include "Adafruit_SSD1306.h"

int main(void)
{

    // <-- Setup -->
    // DDRB = DDRB | (1 << 5 | 1<<4);
    pinMode(13, OUTPUT);
    pinMode(12, OUTPUT);
    int LED13 = 1;
    int LED12 = 1;

    // Serial.begin(9600);
    // <----------->

    // <-- Loop -->
    for(;;){
        // int i;
        for(int i = 0; i < 4; i++){
            // digitalWrite(13, LOW);
            // _delay_ms(100);  /* max is 262.14 ms / F_CPU in MHz */
            delay(100);

            digitalWrite(13, LED13);
            LED13 = 1 - LED13;
            // PORTB = PORTB ^ (1 << 5);
        }
        // PORTB = PORTB ^ (1 << 4);
        LED12 = 1 - LED12;
        digitalWrite(12, LED12 );
        // PORTB ^= 1 << 4;
        // PORTD ^= 1 << 7;    /* toggle the LED */
    }
    // <---------->
    return 0;               /* never reached */
}
