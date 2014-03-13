/*
** SERVO 2 - SWEEP 2
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

// Write a config value to address register on device
void servoConfig(int device, byte address, byte val) {
 Wire.beginTransmission(device); // start transmission to device
 Wire.write(address); // write register address
 Wire.write(val); // write value to write
 Wire.endTransmission(); // end transmission
}

// Write Startup values for each Servo
void servoStartup(int device) {
 unsigned char i;
 Wire.beginTransmission(device); // start transmission to device
 Wire.write(0); // write register address
 for(i=0;i<12;i++) Wire.write(0); // write 0 as startup value for each servo
 // We could easily write different values for
 // each servo
 Wire.endTransmission(); // end transmission
}

// Setup our Servo Configuration
void setup()
{
 Wire.begin(); // join i2c bus (address optional for master)

 // Set Servo Config and Startup values
 servoConfig(servoslave_address, 61, 1); // Extended Mode
 servoConfig(servoslave_address, 62, 0); // Servo Update Rate (0-6)
 servoStartup(servoslave_address); // write Startup values for servos
 servoConfig(servoslave_address, 60, 1); // Servo Output ON
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
