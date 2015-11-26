/********************************************************************
*	Program:	ultrasonic2.ino                                     *
*	Author:		康心奕 Ewing Kang									*
*	Time: 		2015/10/25											*
*	Contect: 	f039281310@yahoo.com.tw								*
*	License:	GPL                   								*
*	About:															*
*                                                                   *
*	Note:															*
*																	*
*********************************************************************/ 
#include <Ultrasonic.h>

#define PIN_TRIG 2   // the trigger pin
#define PIN_ECHO 3

Ultrasonic ultrasonic(PIN_TRIG,PIN_ECHO,30000); // (Trig PIN,Echo PIN)
//變量類型 ultrasonic，上限30000microsec
//int a(17); //==a=17;
void setup() {
    Serial.begin(9600);

}

void loop()
{
    Serial.print(ultrasonic.Timing()); //印出某function 某某變量.Timing(單位)
    Serial.println(" ms  ;" ); // milliseconds
    Serial.print(ultrasonic.Ranging(CM)); // 印出長度 cm
    Serial.println(" cm" );
    delay(500);
}
