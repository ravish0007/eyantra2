



/*
 * PROGRAM FOR SENDING JOYSTICK DATA OVER NRF24L01 
 * JOYSTICKS: 2
 * AXIS: 6
 * DATE:24-12-19
 * VERSION V1.0
 * 
 
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <RF24_config.h>
 */
 #define JS1X A0      //JOYSTICK 1 X-AXIS   DEFINITIONS FOR THE JOYSTICKS
 #define JS1Y A1      //JOYSTICK 1 Y-AXIS

 #define JS2X A4      //JOYSTICK 2 X-AXIS
 #define JS2Y A5      //JOYSTICK 2 Y-AXIS

 #define txBuzz 10    //BUZZER CONN

 RF24 radio(7, 8);    // CE, CSN
 const byte addresses[][6] = {"00001", "00002"};  //[0] for Rx & [1] for Tx

 int txValue ();

 
 void setup() {
  Serial.begin(9600);
  
  pinMode(JS1X,INPUT);
  pinMode(JS1Y,INPUT);
  pinMode(JS2X,INPUT);
  pinMode(JS2Y,INPUT);
  pinMode(txBuzz,OUTPUT);
  digitalWrite(txBuzz,HIGH);          //BUZZEER DEFAULT STATE OFF

  radio.begin();
  radio.openWritingPipe(addresses[1]); // 00002
  radio.openReadingPipe(1, addresses[0]); // 00001
  radio.setPALevel(RF24_PA_MIN);
}

void loop()
{
  int nBuff = txValue ();
  Serial.println(nBuff);
  radio.stopListening();
  radio.write(&NbUFF, sizeof(nBuff));
  delay(5);


/*
Serial.print("JS1X ");
Serial.println(js1xB);
Serial.print("JS1Y ");
Serial.println(js1yB);
Serial.print("JS2X ");
Serial.println(js2xB);
Serial.print("JS2Y ");
Serial.println(js2yB);
Serial.println("");

delay(1000);
*/
}

int txValue ()
{
  int x1= analogRead(JS1X);
  int x2= analogRead(JS2X);
  int y1= analogRead(JS1Y);
  int y2= analogRead(JS2Y);
  int n=0;
  if ((x1 == 0)&& (y1>500))
  {
    n = 6;
  }
   else if ((x1 > 500)&& (y1>1000))
  {
    n = 5;
  }
   else if ((x1 > 1000)&& (y1>500))
  {
    n = 4;
  }
   else if ((x2 > 1000)&& (y2>500))
  {
    n = 3;
  }
   else if ((x2 >500)&& (y2==0))
  {
    n = 2;
  }  
   else if ((x2 == 0)&& (y2>500))
  {
    n = 1;
  }
  else
  {
  n=0;
  }
  return n;
}
