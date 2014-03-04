/*
Objective : Simple console log for the UART line
Assumptions for now:
- Single font size
- Not smooth scroll
*/

#include <Arduino.h>
#include <Wire/Wire.h>
#include <TFT/src/utility/Adafruit_GFX.h>
#include <TFT/src/utility/Adafruit_SSD1306.h>

#define OLED_DC 11
#define OLED_CS 13 //12
#define OLED_CLK 10
#define OLED_MOSI 9
#define OLED_RESET 12 //13
Adafruit_SSD1306 display(OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);

#define DELTAY 2

#define LOGO16_GLCD_HEIGHT 16
#define LOGO16_GLCD_WIDTH  16

#if (SSD1306_LCDHEIGHT != 64)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif

int index = 0;
char incomingMsg[200];
int lineNum = 2;

void testdrawchar(void) {
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);

  for (uint8_t i=0; i < 168; i++) {
    if (i == '\n' || i=='\r') {
      // continue;
    }
    else {
      display.write(i);
      if ((i > 0) && (i % 21 == 0)){
        // display.println();
      }

    }
  }
  display.display();
}

void setup()   {
  Serial.begin(115200);
  Serial.print("\n\n\nRESET!\r\nType at any time!\n\n\n\r");

  // by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
  display.begin(SSD1306_SWITCHCAPVCC);
  display.clearDisplay();


  display.setTextColor(WHITE, BLACK);
  display.setCursor(0,0);
  display.setTextSize(3);
  display.println("Hebe");
  display.setTextSize(2);
  display.println("    and");
  display.setTextSize(3);
  display.println("   Finn");
  display.display(); // show splashscreen
  // delay(100);
  delay(3000);


  display.setTextSize(1);
  display.setCursor(0,0);
  display.clearDisplay();
  display.println("Type away...");
  display.display();

  lineNum = 1;
}


void scrollUp(){
  lineNum =0;
  index = 0;
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE, BLACK);
  display.setCursor(0,0);
}


void chat(){

    char b;
    bool newLine;

    if (Serial.available() > 0) {
        while (Serial.available()>0) {

            newLine = false;

            b = Serial.read();
            index++;
            Serial.print(b);

            if (b=='\r' || b=='\n'){
              newLine = true;
              b='\n';
            }
            if (index == 21){
              newLine = true;
            }
            if (newLine){
              index=0;
              if (lineNum++ >= 7) scrollUp();
            }

            if (b>=32 && b<=126){
              display.write(b);
            }
            else if ((b=='\n') && (lineNum != 0 || index != 0)){
              display.println();
            }
            else {
            }

            display.display();
        }
    }
}

void loop(){
    chat();
}

