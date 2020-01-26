
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>


RF24 radio(7, 8); // CSN, CE
const byte address[6] = "00001";

int joystick_one_x_key = A1;                                               
int joystick_one_y_key = A0;                                               


/*

int joystick_two_x_key = A3 ;                                               
int joystick_two_y_key = A4 ;                                             

*/



int joystick_one_x_pos;
int joystick_one_y_pos;


int joystick_two_x_pos;
int joystick_two_y_pos;







/*

there are four states,   


        Front (0)
Left(3)              Right (1)

        Back(2) // ignored


*/






typedef struct states

{

static const int FRONT = 0;
static const int RIGHT = 1;

 // int BACK  = 2;

static const int LEFT  = 3;

};


states STATE;







/*           # Do this 

you need to estimate the analog signale range for each move of the joystick

also verify if its stable and robust


*/





void setup() {

  Serial.begin(9600) ;   // I added it since it was  missing

  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();

  pinMode (joystick_one_x_key, INPUT) ;                     
  pinMode (joystick_one_y_key, INPUT) ;    


//  pinMode (joystick_two_x_key, INPUT) ;                     
//  pinMode (joystick_two_y_key, INPUT) ;    


}



int  read_joystick()
{


    joystick_one_x_pos = analogRead (joystick_one_x_key) ;
    joystick_one_y_pos = analogRead (joystick_one_y_key) ;


//    joystick_two_x_pos = analogRead (joystick_two_x_key) ;
//    joystick_two_y_pos = analogRead (joystick_two_y_key) ;





    int state = -1 ;

    if ( ( joystick_one_x_pos > 0 ) && ( joystick_one_y_pos > 500 ) )      // Encode values
  
    {
        state = STATE.FRONT ;
    }
   

  

/*

    else if ( ( joystick_two_x_pos > 100 ) && ( joystick_two_y_pos > 500 ) )

    {   
        state = STATE.LEFT ;
    }
  
 
    else if ( ( joystick_two_x_pos < 100 ) && ( joystick_two_y_pos < 500 ) )

    {
        state = STATE.RIGHT ;

    }



*/
  
    else

    { 
        return -1 ;    // Invalid state
    }



    return state ;


}




void loop() 

{

   int state ; 

   state =  read_joystick();

   radio.write(&state, sizeof(state));
   delay(100);

/*    TODO


 
   radio.write(&state_and_token, sizeof(state_and_token));
   delay(100);

   receive( token_from_receiver) ;
   verify_and_buzz( token_from_receiver );
  

*/


}
