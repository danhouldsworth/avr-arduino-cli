/*
** SERVO 1 - SWEEP
**
** Wire Master of Hobbytronics 12 channel SERVO Controller
** Sweeps all 12 servos from one end to the other continuously
** Created 04 Nov 2011
**
** This example code is in the public domain.
** www.hobbytronics.co.uk
*/

#include <Arduino.h>
#include <Wire/Wire.h>

const int servoslave_address=40; // I2C Address of Servo Chip
void setup()
{
 Wire.begin(); // join i2c bus (address optional for master)

 Wire.beginTransmission(servoslave_address); // transmit to device
 Wire.write(60); // servo register address 60
 Wire.write(1); // Turn Servo Outputs ON
 Wire.endTransmission(); // stop transmitting
}


void loop()
{
 unsigned char j;

 Wire.beginTransmission(servoslave_address); // transmit to device
 Wire.write(0); // servo register to start from
 for(j=0;j<12;j++)
 {
 Wire.write(0); // write each servo left
 }
 Wire.endTransmission(); // stop transmitting
 delay(2000); // wait 2 seconds to allow servos to reach end


 Wire.beginTransmission(servoslave_address); // transmit to device
 Wire.write(0); // servo register to start from
 for(j=0;j<12;j++)
 {
 Wire.write(255); // write each servo right
 }
 Wire.endTransmission(); // stop transmitting
 delay(2000); // wait 2 seconds to allow servos to reach end

}
