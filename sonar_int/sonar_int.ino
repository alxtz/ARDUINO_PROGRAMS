/********************************************************************
*	Program:	InoRcServo.ino                                     *
*	Author:		康心奕 Ewing Kang									*
*	Time: 		2015/11/12											*
*	Contect: 	f039281310@yahoo.com.tw								*
*	License:	GPL                   								*
*	About:															*
*		                                                            *
*																	*
*	Note:															*
*																	*
*********************************************************************/ 

#include <PinChangeInt.h>    // http://playground.arduino.cc/Main/PinChangeInt

#define NO_PORTB_PIN_CHANGES    //pin_rcChangeInt setup
#define NO_PORTC_PIN_CHANGES    //only port D pin_rcchanges (see: http://playground.arduino.cc/Learning/pin_rcs)

#define MAX_PIN_CHANGE_PINS 1

#define PIN_TRIG 2   // the trigger pin
#define PIN_ECHO 3

#define MAX_PERD 30303     //maximum period 5m * 2 (ways) / 330 (m/s) * 10^6 micros/sec

unsigned long echo_rise, echo_fall;
unsigned long last_chg_time;   // 
unsigned int echo_time;               // 

bool snr_active = false;         // sonar activation flag

void setup() {
    Serial.begin(115200);
    Serial.print("initialize the Line Dectector program");

    pinMode(PIN_TRIG, OUTPUT);
    digitalWrite(PIN_TRIG, LOW);
    pinMode(PIN_ECHO, INPUT);
    
}

void loop() {
    Serial.println("run!");

    if(snr_active != true) {
        Serial.println("Sending soundwave  ;");
        digitalWrite(PIN_TRIG, HIGH);
        delayMicroseconds(10);
        digitalWrite(PIN_TRIG, LOW);
        snr_active = true;
        PCintPort::attachInterrupt(PIN_ECHO, snr_rise,RISING);
    
    }

    unsigned long time_last = last_chg_time;    // make a snapshot incase inturrupt happened
    unsigned long time_now = micros();    
    if( (time_now > time_last) && ((time_now - time_last) >= MAX_PERD) ) // sometimes 
    {
        Serial.println("miss!");
        PCintPort::detachInterrupt(PIN_ECHO);
        snr_active = false;
        last_chg_time = micros();
    }
}


void snr_rise()        // on the rising edge of the currently intresting pin
{
    echo_rise = micros();
    PCintPort::detachInterrupt(PIN_ECHO);
    PCintPort::attachInterrupt(PIN_ECHO, snr_fall, FALLING); //attach the falling end
    
    last_chg_time = echo_rise;
}


void snr_fall()        //on the falling edge of the signal
{
    echo_fall = micros();
    echo_time = echo_rise - echo_fall;
    snr_active = false;
    
    PCintPort::detachInterrupt(PIN_ECHO);
        
    last_chg_time = echo_fall;
}






