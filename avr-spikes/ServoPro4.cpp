/*
** SERVO 4 - QUADCOPTER
**
** Wire Master of Hobbytronics 12 channel SERVO Controller
** Sweeps all 12 servos from one end to the other continuously
** at 400Hz
** Created 04 Nov 2011
**
** This example code is in the public domain.
** www.hobbytronics.co.uk
*/

#include <Arduino.h>
#include <Wire/Wire.h>

const int servoslave_address=40; // I2C Address of Servo Chip

// Write a config value to address register on device
void servoConfig(int device, byte address, byte val) {
 Wire.beginTransmission(device); // start transmission to device
 Wire.write(address); // send register address
 Wire.write(val); // send value to write
 Wire.endTransmission(); // end transmission
}

// Write Startup values for each Servo
void servoStartup(int device) {
 unsigned char i;
 Wire.beginTransmission(device); // start transmission to device
 Wire.write(0); // send register address
 for(i=0;i<12;i++) Wire.write(0); // send 0 as startup value for each servo
 // We could easily send different values for
 // each servo
 Wire.endTransmission(); // end transmission
}

// Setup our Servo Configuration
void setup()
{
 Wire.begin(); // join i2c bus (address optional for master)

 // Set Servo Config and Startup values
 servoConfig(servoslave_address, 61, 1); // Extended Mode
 servoConfig(servoslave_address, 62, 6); // Servo Update Rate (6=400Hz)
 servoStartup(servoslave_address); // Send Startup values for servos
 servoConfig(servoslave_address, 60, 1); // Servo Output ON
}

void loop()
{
 unsigned char j;

 Wire.beginTransmission(servoslave_address); // transmit to device
 Wire.write(0); // servo register to start from
 for(j=0;j<4;j++)
 {
 	Wire.write(0); // send each servo left
 }
 Wire.endTransmission(); // stop transmitting
 delay(2000); // wait 2 seconds to allow servos to reach end


 Wire.beginTransmission(servoslave_address); // transmit to device
 Wire.write(0); // servo register to start from
 for(j=0;j<4;j++)
 {
 Wire.write(255); // send each servo right
 }
 Wire.endTransmission(); // stop transmitting
 delay(2000); // wait 2 seconds to allow servos to reach end

}
