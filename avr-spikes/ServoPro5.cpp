/*
** SERVO 5 – Read Servo Position
**
** Wire Master of Hobbytronics 12 channel SERVO Controller (Version 2)
** Created 04 Nov 2011
**
** This example moves the servo 0 from full left to full right and back
** again with a speed setting of 4 seconds.
** By reading the current position of servo 0 we can determine when it is
** at the halfway point and move servo 1 full right immediately.
** A similar function is applied when the servo 0 is on the way back
** when it reaches half way, servo 1 is returned back to full left.
** This example code is in the public domain.
** www.hobbytronics.co.uk
*/

#include <Arduino.h>
#include <Wire/Wire.h>

const int servoslave_address=40; // I2C Address of ADC Chip
unsigned char servo_pos;

// Write a config value to address register on device
void servoConfig(int device, byte address, byte val) {
 Wire.beginTransmission(device); // start transmission to device
 Wire.write(address); // send register address
 Wire.write(val); // send value to write
 Wire.endTransmission(); // end transmission
}

// Send a position command to a Servo
void servoPos(int device, byte servo, byte pos) {
 Wire.beginTransmission(device); // start transmission to device
 Wire.write(servo); // send servo register address
 Wire.write(pos); // send position value for servo
 Wire.endTransmission(); // end transmission

}

// Write Startup values for each Servo
void servoStartup(int device) {
 unsigned char i;

 // Clear any speed settings for all servos
 Wire.beginTransmission(device); // start transmission to device
 Wire.write(63); // send register address
 for(i=0;i<12;i++) Wire.write(0); // send 0 as speed value for each servo
 Wire.endTransmission(); // end transmission

 // Set every servo at position 0 - change this if you want start positions
 // to be different.
 Wire.beginTransmission(device); // start transmission to device
 Wire.write(0); // send register address
 for(i=0;i<12;i++) Wire.write(0); // send 0 as startup value for each servo
 	 Wire.endTransmission(); // end transmission

}

// Read current position for a Servo
unsigned char getservoPos(int device, byte servo_num) {
 unsigned char servoPosition;

 //Send the Servo number to read
 Wire.beginTransmission(device); // start transmission to device
 Wire.write(servo_num); // send register address (servo number)
 Wire.endTransmission(); // end transmission

 //Request servo position
 Wire.requestFrom(device, 1); // request 1 byte from slave device
 if(Wire.available())
 {
 servoPosition = Wire.read(); // receive a byte as character
 }
 return servoPosition;

}

void setup()
{
 Wire.begin(); // join i2c bus (address optional for master)

 // Set Servo Config and Startup values
 servoConfig(servoslave_address, 61, 1); // Extended Mode
 servoConfig(servoslave_address, 62, 0); // Servo Update Rate (0-6)
 servoStartup(servoslave_address); // Send Startup values for servos
 // and clear speed settings
 servoConfig(servoslave_address, 63, 40); // Servo Speed set to 4 seconds (Servo 0)
 servoConfig(servoslave_address, 60, 1); // Servo Output ON

 // Add a delay here to give servos time to move to startup position

}

void loop()
{
 unsigned char i,j;

 // Send servo 0 full right (speed is 4 seconds)
 servoPos(servoslave_address, 0, 255);

 // Read position of servo 0, when it gets to center move servo 1 full right
 while(1)
 {
 delay(2); // waits
 servo_pos = getservoPos(servoslave_address, 0);
 if(servo_pos>=125) break;
 }

 // move servo 1 full RIGHT
 servoPos(servoslave_address, 1, 255);

 // Read position of servo 0, when it gets to full right, send it back to full left
 while(1)
 {
 delay(2); // waits
 servo_pos = getservoPos(servoslave_address, 0);
 if(servo_pos>=255) break;
 }

 // send servo 0 back to full left
 servoPos(servoslave_address, 0, 0);

 // Read position of servo 0, when it gets to center move servo 1 full LEFT
 while(1)
 {
 delay(2); // waits
 servo_pos = getservoPos(servoslave_address, 0);
 if(servo_pos<=125) break;
 }

 // move servo 1 full LEFT
 servoPos(servoslave_address, 1, 0);

 // wait unti servo 0 gets back to 0, then loop
 while(1)
 {
 delay(2); // waits
 servo_pos = getservoPos(servoslave_address, 0);
 if(servo_pos<=0) break;
 }

}
