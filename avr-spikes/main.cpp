// main.cpp

/************************************************************

A simple test script to check that ISP and build have worked:

1) Cycles (LEDs on) pins LED1pin and LED2pin

2) Echo's back anything recieved on Rx

3) Sends a simple message on Tx

************************************************************/

#define ratioPin1to2 4
#define delayInMS 250
#define LED1pin 12
#define LED2pin 13

#include <Arduino.h>

// Globals
const char *pins[] = {"OFF", "ON"};
int LED1status = 1;
int LED2status = 1;
int index = 0;
char incomingMsg[100];
// --

void blink(){

    for(int i = 0; i < ratioPin1to2; i++){
        delay(delayInMS);
        digitalWrite(LED1pin, LED1status);
        LED1status = 1 - LED1status;
    }
    LED2status = 1 - LED2status;
    digitalWrite(LED2pin, LED2status );
    Serial.print("LED2 is set to : ");
    Serial.print(pins[LED2status]);
    Serial.print("\n\r");
}

int chat(){

    if (Serial.available() > 0) {
        while (Serial.available()>0) {
            Serial.print(incomingMsg[index++] = Serial.read());
        }
        if (incomingMsg[index-1] == '\r' || incomingMsg[index-1] == '\n'){
            Serial.print("ATmega328 ECHO Back : ");
            Serial.print(incomingMsg);
            Serial.print("\n\r");
            index = 0;
        }
    }

    return index;
}

void setup() {

    pinMode(LED2pin, OUTPUT);
    pinMode(LED1pin, OUTPUT);

    Serial.begin(9600);
    Serial.print("\n\n\nRESET!\r\nType at any time!\n\n\n\r");
}

void loop(){

    chat();

    if (index == 0) {
        blink();
    }
}
