/********************************************************************
*	Program:	servo.ino                                     *
*	Author:		康心奕 Ewing Kang									*
*	Time: 		2015/10/25											*
*	Contect: 	f039281310@yahoo.com.tw								*
*	License:	GPL                   								*
*	About:															*
*                                                                   *
*	Note:															*
*																	*
*********************************************************************/ 

#define PIN_SVO 4       // the trigger pin
#define MAX_SVO 160     // maximum servo angle
#define MIN_SVO 20
#include <Servo.h> 
 
Servo snr_servo;  // create servo object to control a servo 
                // twelve servo objects can be created on most boards
int pos = 90;    // variable to store the servo position 
 
void setup() 
{ 
    Serial.begin(9600);
    Serial.print("servo start please enter position");
    Serial.setTimeout(1);        // for  Serial.parseInt() 
  snr_servo.attach(PIN_SVO);  // attaches the servo on pin 9 to the servo object 
} 
 
void loop() 
{ 
    if(Serial.available()) {
        pos = Serial.parseInt();
        if (pos>MAX_SVO) pos = MAX_SVO;
        if (pos<MIN_SVO) pos = MIN_SVO;
    }
    snr_servo.write(pos);              // tell servo to go to position in variable 'pos' 
    delay(80);     // waits 15ms for the servo to reach the position 
    Serial.print("servo position:");
    Serial.println(pos);
} 
