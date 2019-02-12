//calling newPing library to control ultrasoinc
#include <NewPing.h>
//define all the state that we have in the FSM
enum {Idle,MovingForward,Backward,Turnleft,Turnright,Turn,AM_Backward,AM_MovingForward};
//define initial state to be Idle
int currentState = Idle; 
// define the speed for the 4 motor to controll them later
int bmr,bml,smr,sml;
//right back motor(PWM)
#define Enable11 11
//right back motor(direction)
#define ControlMotor13 13
#define ControlMotor12 12
///left back motor(PWM)
#define Enable10 10
///left back motor(direction)
#define ControlMotor9 9
#define ControlMotor8 8
///left small motor(PWM)
#define Enable6 6
///left small motor(direction)
#define ControlMotor7 7
#define ControlMotor5 5
///right small motor(PWM)
#define Enable3 3
///right small motor(direction)
#define ControlMotor4 4
#define ControlMotor2 2
//define the state that we gone use to read the output from the blutooth
int state;
/////////////////////////////
//PIZO
#define buzzerPin A2
//define freucancy srt of(STAR WAR Song)
const int c = 261;const int d = 294;const int e = 329;const int f = 349;const int g = 391;const int gS = 415;const int a = 440;const int aS = 455;const int b = 466;const int cH = 523;const int cSH = 554;const int dH = 587;const int dSH = 622;const int eH = 659;const int fH = 698;const int fSH = 740;const int gH = 784;const int gSH = 830;const int aH = 880;
//counter for the pizo delay
int counter = 0;
//IR (edge sensor)
#define IRS A5
//ultrasoinc (distance sensor)
#define TRIGGER_PIN A0
#define ECHO_PIN     A1
//the MAX DISTANCE that the Ultrasoinc will detect
#define MAX_DISTANCE 200
//define the paremter for sonar method from the NewPing libray 
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

void setup() {
//display Output in the serial monitor,buad is 9600
Serial.begin(9600);  
//PIZO is an Output
pinMode(buzzerPin,OUTPUT);
//(PWM pin)to controll the speed for back right motor
pinMode(Enable11, OUTPUT);
//(PWM pin)to controll the speed for back left motor
pinMode(Enable10, OUTPUT);
//(PWM pin)to controll the speed for small left motor
pinMode(Enable6, OUTPUT);
//(PWM pin)to controll the speed for small right motor
pinMode(Enable3, OUTPUT);
//to controll the diraction of the back right motor
pinMode(ControlMotor13, OUTPUT);
pinMode(ControlMotor12, OUTPUT);
//to controll the diraction of the back left motor
pinMode(ControlMotor9, OUTPUT);
pinMode(ControlMotor8, OUTPUT);
//to controll the diraction of the small left motor
pinMode(ControlMotor7, OUTPUT);
pinMode(ControlMotor5, OUTPUT);
//to controll the diraction of the small right motor
pinMode(ControlMotor4, OUTPUT);
pinMode(ControlMotor2, OUTPUT);
 }



void loop() {
    //Calling IRInputCheck method which will check the output from the Buletooth
    IRInputCheck();}



//PIZO(StarWar) START
//beep method take two paremters(frecuany and duration).
void beep(int note, int duration)
{if(state=='V'){tone(buzzerPin, note, duration);if(counter % 2 == 0){delay(duration);}else{delay(duration);}noTone(buzzerPin);delay(50);counter++;}}
//this is the first saction of the star war song
void firstSection(){
 beep(a,500);beep(a,500);beep(a,500);beep(f,350);beep(cH,150);beep(a,500);beep(f,350);beep(cH,150);beep(a,650);
 delay(500);
 beep(eH,500);beep(eH,500);beep(eH,500);beep(fH,350);beep(cH,150);beep(gS,500);beep(f,350);beep(cH,150);beep(a,650);
 delay(500);}
//this is the second saction of the star war song
void secondSection(){
 beep(aH,500);beep(a,300);beep(a,150);beep(aH,500);beep(gSH,325);beep(gH,175);beep(fSH,125);beep(fH,125);beep(fSH,250);
 delay(325);
 beep(aS,250);beep(dSH,500);beep(dH,325);beep(cSH,175);beep(cH,125);beep(b,125);beep(cH,250);  
 delay(350);}
//this is the third saction of the star war song
void thardpart(){beep(f,250);beep(gS,500);beep(f,350);beep(a, 125);beep(cH,500);beep(a,375);beep(cH,125);beep(eH,650);
  delay(500);
  secondSection();beep(f,250);beep(gS,500);beep(f,375);beep(cH,125);beep(a,500);beep(f,375);beep(cH,125);beep(a,650);  
  delay(650);}
//PIZO END


//this method lisean for the  BLUETHOOTH
void IRInputCheck() {
  //cheack if there is signal coming from the bluethooth
  if(Serial.available() > 0){
    //we set the state to what the bluetooth send     
      state = Serial.read();}
    //chack the state output
    //state can be 3 type of button
    //(Swith Button)first press (on),second press (off)
    //(Press Button)pressing (on),stop pressing (off) 
    //(moveing bar)eacth move for the bar triger a diffrent button.    
    switch (state) {
      //when no button is pressed 
       default :
        Serial.println("Idle");
        //currentState go to the Idle
        currentState = Idle;
            //shut down all motors
            digitalWrite(ControlMotor13, LOW);
            digitalWrite(ControlMotor12, LOW);
            digitalWrite(ControlMotor9, LOW);
            digitalWrite(ControlMotor8, LOW);
            digitalWrite(ControlMotor7, LOW);
            digitalWrite(ControlMotor5, LOW);
            digitalWrite(ControlMotor4, LOW);
            digitalWrite(ControlMotor2, LOW);
        break;
      //when X is pressed(Swith Button)
      case 'X':
        //currentState go to the AM_MovingForward
        //this is the auto obstacle avoider
       currentState = AM_MovingForward;
       //if the currentState is  AM_MovingForward
       if (currentState == AM_MovingForward) {
            Serial.println("AM_MovingForward");
            //set the speed of the motors
            analogWrite(Enable11, bmr);  analogWrite(Enable10, bml);
            analogWrite(Enable6, smr);  analogWrite(Enable3, sml);
            //all motors go forward 
            digitalWrite(ControlMotor13, LOW);
            digitalWrite(ControlMotor12, HIGH);
            digitalWrite(ControlMotor9, LOW);
            digitalWrite(ControlMotor8, HIGH);
            digitalWrite(ControlMotor7, LOW);
            digitalWrite(ControlMotor5, HIGH);
            digitalWrite(ControlMotor4, LOW);
            digitalWrite(ControlMotor2, HIGH);
            //if the car about to fall 
            if (digitalRead(IRS) == HIGH)
                //currentState is  AM_Backward
                currentState = AM_Backward ;
            //if the car about to hit somthing that far from us 8cm 
            //snor.ping_cm retuen the distance of the object in cm
            if(sonar.ping_cm()<8 && sonar.ping_cm()>0 )
                //currentState is  AM_Backward
                currentState = AM_Backward ; 
         }
       //if the currentState is  AM_MovingForward    
       if (currentState == AM_Backward) {
             Serial.println("AM_Backward");
            //set the speed of the motors
            analogWrite(Enable11, bmr);  analogWrite(Enable10, bml);
            analogWrite(Enable6, smr);  analogWrite(Enable3, sml); 
            //all motors go backward                                  
            digitalWrite(ControlMotor13, HIGH);
            digitalWrite(ControlMotor12, LOW);
            digitalWrite(ControlMotor9, HIGH);
            digitalWrite(ControlMotor8, LOW);
            digitalWrite(ControlMotor7, HIGH);
            digitalWrite(ControlMotor5, LOW);
            digitalWrite(ControlMotor4, HIGH);
            digitalWrite(ControlMotor2, LOW);
            //wait 2 s
            delay(2000);
             //currentState is  Turn
             currentState = Turn;
       }
       if (currentState == Turn) {
            Serial.println("Turn");
            //set the speed of the motors
            analogWrite(Enable11, bmr);  analogWrite(Enable10, bml);
            analogWrite(Enable6, smr);  analogWrite(Enable3, sml); 
            //motors  Turn Right                                  
            digitalWrite(ControlMotor13, HIGH);
            digitalWrite(ControlMotor12, LOW);
            digitalWrite(ControlMotor9, LOW);
            digitalWrite(ControlMotor8, LOW);
            digitalWrite(ControlMotor7, HIGH);
            digitalWrite(ControlMotor5, LOW);
            digitalWrite(ControlMotor4, LOW);
            digitalWrite(ControlMotor2, LOW);
            //wait 2 s
            delay(2000);
            //currentState is  AM_MovingForward(after we escape the obstacle we continue moving)
            currentState = AM_MovingForward;
       }
       break;
      //when F is pressed(press button)
      case 'F':
      //currentState is  MovingForward
      currentState = MovingForward;
      if(currentState==MovingForward){
          Serial.println("Moving Forward");
            //set the speed of the motors
            analogWrite(Enable11, bmr);  analogWrite(Enable10, bml);
            analogWrite(Enable6, smr);  analogWrite(Enable3, sml);
            //all motors go forward                                  
            digitalWrite(ControlMotor13, LOW);
            digitalWrite(ControlMotor12, HIGH);
            digitalWrite(ControlMotor9, LOW);
            digitalWrite(ControlMotor8, HIGH);
            digitalWrite(ControlMotor7, LOW);
            digitalWrite(ControlMotor5, HIGH);
            digitalWrite(ControlMotor4, LOW);
            digitalWrite(ControlMotor2, HIGH); 
            //if the car about to fall 
            if (digitalRead(IRS) == HIGH)
            //move back
            state='B';
           }
      //when B is pressed(press button)
      case 'B':
             Serial.println("Backward");
            //currentState is  Backward
             currentState = Backward;
            //set the speed of the motors
            analogWrite(Enable11, bmr);  analogWrite(Enable10, bml);
            analogWrite(Enable6, smr);  analogWrite(Enable3, sml);
            //all motors go backward                                            
            digitalWrite(ControlMotor13, HIGH);
            digitalWrite(ControlMotor12, LOW);
            digitalWrite(ControlMotor9, HIGH);
            digitalWrite(ControlMotor8, LOW);
            digitalWrite(ControlMotor7, HIGH);
            digitalWrite(ControlMotor5, LOW);
            digitalWrite(ControlMotor4, HIGH);
            digitalWrite(ControlMotor2, LOW);
            //if the car about to fall           
             if (digitalRead(IRS) == HIGH)
            //move fowrard
             state='F' ; 
        break;
      //when R is pressed(press button) 
      case 'R':
        Serial.println("Turn right");
      //currentState is  Turnright
        currentState = Turnright;
            //set the speed of the motors
            analogWrite(Enable11, bmr);  analogWrite(Enable10, bml);
            analogWrite(Enable6, smr);  analogWrite(Enable3, sml); 
            //motors Turnright                                           
            digitalWrite(ControlMotor13, HIGH);
            digitalWrite(ControlMotor12, LOW);
            digitalWrite(ControlMotor9, LOW);
            digitalWrite(ControlMotor8, LOW);
            digitalWrite(ControlMotor7, HIGH);
            digitalWrite(ControlMotor5, LOW);
            digitalWrite(ControlMotor4, LOW);
            digitalWrite(ControlMotor2, LOW);
        break;
      //when L is pressed(press button)  
      case 'L':
        Serial.println("Turn left");
        //currentState is  Turnleft
        currentState = Turnleft;
            //set the speed of the motors
            analogWrite(Enable11, bmr);  analogWrite(Enable10, bml);
            analogWrite(Enable6, smr);  analogWrite(Enable3, sml); 
            //motors Turnleft                                                 
            digitalWrite(ControlMotor13, LOW);
            digitalWrite(ControlMotor12, HIGH);
            digitalWrite(ControlMotor9, LOW);
            digitalWrite(ControlMotor8, LOW);
            digitalWrite(ControlMotor7, LOW);
            digitalWrite(ControlMotor5, HIGH);
            digitalWrite(ControlMotor4, LOW);
            digitalWrite(ControlMotor2, LOW);
        break;
      //when V is pressed(Swith Button)
      case 'V':
        Serial.println("PIZO");
        //play the (Star war song)
        firstSection();
        secondSection();
        thardpart();
        break;

      //controll the speed  
      //when 0 is pressed(moveing bar)  
      case '0':
        //set the speed to 0
        bmr=0;bml=0;smr=0;sml=0;
        break;
      //when 1 is pressed(moveing bar)  
      case '1':
        //set the speed to 25
        bmr=25;bml=25;smr=25;sml=25;
        break;
      //when 2 is pressed(moveing bar)            
      case '2':
        //set the speed to 50
         bmr=50;bml=50;smr=50;sml=50;
        break;
      //when 3 is pressed(moveing bar)            
      case '3':
        //set the speed to 80
        bmr=80;bml=80;smr=80;sml=80;
        break;
      //when 4 is pressed(moveing bar)    
      case '4':
        //set the speed to 100
        bmr=100;bml=100;smr=100;sml=100;
        break;
      //when 5 is pressed(moveing bar)    
      case '5':
        //set the speed to 125
        bmr=125;bml=125;smr=125;sml=125;
         break;
      //when 6 is pressed(moveing bar)    
      case '6':
        //set the speed to 150
        bmr=150;bml=150;smr=150;sml=150;
         break; 
      //when 7 is pressed(moveing bar)    
      case '7':
        //set the speed to 180
        bmr=180;bml=180;smr=180;sml=180;
         break;
      //when 8 is pressed(moveing bar)    
      case '8':
        //set the speed to 205
        bmr=205;bml=205;smr=205;sml=205;
         break;  
      //when 9 is pressed(moveing bar)    
      case '9':
        //set the speed to 225
        bmr=225;bml=225;smr=225;sml=225;
         break;
      //when q is pressed(moveing bar)    
      case 'q':
        //set the speed to 255
        bmr=255;bml=255;smr=255;sml=255;
        break;
       }
  } 
//BLUETHOOTH END  
