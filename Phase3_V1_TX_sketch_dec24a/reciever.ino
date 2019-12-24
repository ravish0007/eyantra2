/*
 * PROGRAM FOR SENDING JOYSTICK DATA OVER NRF24L01 RECEIVER SIDE
 * SERVOS: 6
 * DATE:24-12-19
 * VERSION V1.0
 * 
 */

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <RF24_config.h>
#include <Servo.h>

RF24 radio(7, 8);       // CE, CSN
const byte addresses[][6] = {"00001", "00002"};
Servo myServo1;
Servo myServo2;
Servo myServo3;
Servo myServo4;
Servo myServo5;
Servo myServo6;

int jsState=0;

void setup()
{
  Serial.begin(9600);
  radio.begin();
  radio.openWritingPipe(addresses[0]); // 00001
  radio.openReadingPipe(1, addresses[1]); // 00002
  radio.setPALevel(RF24_PA_MIN);

  myServo1.attach("ADD THE PIN"); //SERVO PIN INIT 
  myServo2.attach("ADD THE PIN");
  myServo3.attach("ADD THE PIN");
  myServo4.attach("ADD THE PIN");
  myServo5.attach("ADD THE PIN");
  myServo6.attach("ADD THE PIN");

  myServo1.write(0);              //SERVO INIT
  myServo2.write(0);
  myServo3.write(0);
  myServo4.write(0);
  myServo5.write(0);
  myServo6.write(0);
}

void loop()
{
  radio.startListening();
  while (!radio.available());
  radio.read(&jsState, sizeof(jsState));
  Serial.println(jsState);
  delay(5);
  
}
