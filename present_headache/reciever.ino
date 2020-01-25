#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Servo.h>




Servo servo_one   ;       // forward


Servo servo_two   ;       // dorsal left
Servo servo_three ;       // dorsal right



RF24 radio(7, 8); // CSN, CE
const byte address[6] = "00001";



int servo_pin_one   = 2;
int servo_pin_two   = 3;
int servo_pin_three = 4;




/*

there are four states,   


        Front (0)
Left(3)              Right (1)

        Back(2) // ignored


*/




typedef struct states

{

  int FRONT = 0;
  int RIGHT = 1;

 // int BACK  = 2;

  int LEFT  = 3;

};


states STATE;


void setup() 

{


  Serial.begin(9600);
  radio.begin();

  //-------- servos init---------

  servo_one.attach(servo_pin_one ) ; 
  servo_two.attach(servo_pin_two ) ; 
  servo_three.attach(servo_pin_three ) ; 
  

  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();


}



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






void move_serveo(state)

{


    int angle_bank = 150 ;  // for dorsal fins, better we implement propotional to the voltage 

    switch(state)

    {


     case STATE.FRONT :   servo_one.write(0)   ;
                          _delay_ms(1000)      ;          // Son adjust delay accordingly       
                          servo_one.write(180) ;
                          _delay_ms(1000)      ;       
                          servo_one.write(90)  ;
                                         break ;

     case STATE.RIGHT :   
                          servo_two.write(angle_bank)         ;
                          servo_three.write(180 - angle_bank) ;
                          _delay_ms(1000)                     ;        // again adjust here
                                                        break ; 
                                                              
     case STATE.LEFT :   
                          servo_two.write(180 - angle_bank)   ;        // Just anti rotate
                          servo_three.write(angle_bank)       ;
                          _delay_ms(1000)                     ;        // again adjust here
                                                        break ;  


     default : Serial.println("Error in transmission, Exception at move_servo  ");



    }


}









void loop() 

{



  if (radio.available()) 
    
    {



        int state ;
        radio.read(&state, sizeof(state));

        print_state(state); 


/*        # TODO:

        parse(state_and_token)
        Serial.println(" Transmission token " );
        
        verify_token_and_acknowledge();

*/


        move_servo(state)
    

       }


}



    

        

