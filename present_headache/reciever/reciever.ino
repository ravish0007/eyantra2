#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Servo.h>




Servo servo_one   ;       // forward


Servo servo_two   ;       // dorsal left
Servo servo_three ;       // dorsal right


int delay_forward = 15 ;


RF24 radio(7, 8); // CSN, CE
const byte address[6] = "00001";


// TODO : sperate channel allocation for transmitter



int servo_pin_one   = 5;
int servo_pin_two   = 4;
int servo_pin_three = 3;

int tail_servo;
int left_servo;
int right_servo;


int positional_array[2] ;








/*

there are four states,   


        Front (0)
Left(3)              Right (1)

        Back(2) // ignored


*/




typedef struct states

{

    static const  int FRONT = 0;
    static const  int RIGHT = 1;

    //static const int BACK  = 2;

    static const  int LEFT = 3;

};




void setup() 

{


  Serial.begin(9600);
  radio.begin();

  //-------- servos init---------

  servo_one.attach(servo_pin_one ) ; 
  servo_two.attach(servo_pin_two ) ; 
  servo_three.attach(servo_pin_three ) ; 
  

  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MAX);
  radio.startListening();


}


states STATE ;

void print_state(int state)

{


    switch(state)

    {


     case STATE.FRONT :   Serial.println(" Forward ")   ; break ;

     case STATE.RIGHT :   Serial.println(" Right ")     ; break ; 

     case STATE.LEFT  :   Serial.println(" Left ")      ; break ; 

     default : printf("Error in transmission ");



    }




}




void change_velocity()
{


  if ( delay_forward == 1 )
  {

    return ;
  }
  
  else {
    
  

  





          for (int pos = 1; pos <= 180; pos += 1) 
          {
   
           servo_one.write(pos);              
           delay(delay_forward);                      
          }

        for (int pos = 180; pos >= 1; pos -= 1) 
          {
   
          servo_one.write(pos);              
           delay(delay_forward);                      
          }
  
    }


}

void move_serveo()

{


  tail_servo  = positional_array[1] ;
  left_servo  = positional_array[0] ;
  right_servo = 180 - left_servo ;


  if (  tail_servo != 91)
  {
     if ( tail_servo > 91 )
     {
      
      delay_forward = 4 ;
      
     }

    else if ( tail_servo < 91 )
     {
      
      delay_forward = 2 ;
      
     }   
  
  }


  else
  {
      delay_forward = 1 ;
    
  }

  
  servo_two.write(left_servo);
  servo_three.write(right_servo);


}







void recieve_radio()

{

        radio.read(&positional_array, sizeof(positional_array));


        Serial.println(positional_array[0]);
        Serial.println(positional_array[1]);
        Serial.println("---------------------");

        delay(100);
}

void loop() 

{




 change_velocity();

 
  if (radio.available()) 
    
    {

         recieve_radio() ;





/*        # TODO:

        parse(state_and_token)
        Serial.println(" Transmission token " );
        
        verify_token_and_acknowledge();

*/


        move_serveo();
    

       }


}



    

        
