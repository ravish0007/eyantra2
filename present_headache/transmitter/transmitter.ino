
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>


RF24 radio(7, 8); // CSN, CE
const byte address[6] = "00001";

int joystick_one_x_key = A1;                                               
int joystick_one_y_key = A0;                                               




int joystick_two_x_key = A2 ;                                               
int joystick_two_y_key = A3 ;                                             





int joystick_one_x_pos;
int joystick_one_y_pos;


int joystick_two_x_pos;
int joystick_two_y_pos;




int prev_joystick_one_x_pos = 89;
int prev_joystick_one_y_pos;


int prev_joystick_two_x_pos;
int prev_joystick_two_y_pos = 93;




int positional_array[2] ;



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
  radio.setPALevel(RF24_PA_MAX);
  radio.stopListening();

  pinMode (joystick_one_x_key, INPUT) ;                     
  pinMode (joystick_one_y_key, INPUT) ;    


  pinMode (joystick_two_x_key, INPUT) ;                     
  pinMode (joystick_two_y_key, INPUT) ;    


}



void  read_joystick()
{

  prev_joystick_one_x_pos = joystick_one_x_pos ;
  prev_joystick_two_y_pos = joystick_one_x_pos ;


  joystick_one_x_pos = analogRead (joystick_one_x_key) ;  
  joystick_one_y_pos = analogRead (joystick_one_y_key) ; 

  
  joystick_two_x_pos = analogRead (joystick_two_x_key) ; 
  joystick_two_y_pos = analogRead (joystick_two_y_key) ; 


  joystick_one_x_pos = map(joystick_one_x_pos, 0 , 1023, 0, 180);
  joystick_one_y_pos = map(joystick_one_y_pos, 0 , 1023, 0, 180);
  joystick_two_x_pos = map(joystick_two_x_pos, 0 , 1023, 0, 180);
  joystick_two_y_pos = map(joystick_two_y_pos, 0 , 1023, 0, 180);

  positional_array[0] = joystick_one_x_pos;
  positional_array[1] = joystick_two_y_pos;

  Serial.println(joystick_one_x_pos);
  Serial.println(joystick_two_y_pos);
  Serial.println("---------------------");


}



void send_radio()

{

if ( ( prev_joystick_two_y_pos != joystick_two_y_pos ) ||  ( prev_joystick_two_y_pos != prev_joystick_two_y_pos ) )
{

radio.write(&positional_array, sizeof(positional_array));
//radio.write(&joystick_one_x_pos, sizeof(joystick_one_x_pos));
}
  
}


void loop() 

{


  read_joystick();

  
   send_radio();
   
   delay(10);

/*    TODO


 
   radio.write(&state_and_token, sizeof(state_and_token));
   delay(100);

   receive( token_from_receiver) ;
   verify_and_buzz( token_from_receiver );
  

*/


}
