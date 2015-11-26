/********************************************************************
*	Program:	InoRcServo.ino                                     *
*	Author:		康心奕 Ewing Kang									*
*	Time: 		2015/10/14											*
*	Contect: 	f039281310@yahoo.com.tw								*
*	License:	GPL                   								*
*	About:															*
*		This Arduino program takes in 3 receiver signals and write  *
*       servo output with efficient interrupt method.               *
*																	*
*	Note:															*
*																	*
*********************************************************************/ 
#include <Servo.h>
#include <PinChangeInt.h>    // http://playground.arduino.cc/Main/PinChangeInt
#include <TimerOne.h>        // http://playground.arduino.cc/Code/Timer1

#define NO_PORTB_PIN_CHANGES //pin_rcChangeInt setup
#define NO_PORTC_PIN_CHANGES    //only port D pin_rcchanges (see: http://playground.arduino.cc/Learning/pin_rcs)
#define PIN_RC_COUNT 3    //number of channels attached to the reciver
#define MAX_PIN_CHANGE_PINS PIN_RC_COUNT

#define RC_MAX_PERD 22000     //maximum period of RC input

#define FREQ_LOOP 200                   // frequency of the main loop
#define PERIOD_LOOP 1000/FREQ_LOOP      // period of RC in milliseconds
#define PWM_MAX 2200
#define PWM_MIN 800

#define RC_COUNT 3      // how many receiver input pins
#define RC_TRN 4        // arduino pins attached to the reciver
#define RC_FWD 5
#define RC_SWITCH 6
byte pin_rc[] = {RC_FWD, RC_TRN, RC_SWITCH};    //for maximum efficency thise pin_rcs should be attached
#define IND_RC_FWD 0    // index for RC pins    
#define IND_RC_TRN 1
#define IND_RC_SWITCH 2
unsigned long rc_rise[RC_COUNT], rc_fall[RC_COUNT];     // time recorder
unsigned int rc_pwm[] = {0,0,0};                // to the reciver's channels in the order listed here

#define SERVO_COUNT 2   // how many output servos are attached
#define SERVO_FWD   9   // arduino pins attached to the servos
#define SERVO_TRN  10
byte pin_servo[] = {SERVO_FWD, SERVO_TRN};    //for maximum efficency thise pin_rcs should be attached
#define IND_SVO_FWD 0   // index for servo pins
#define IND_SVO_TRN 1
Servo svo[SERVO_COUNT]; // servo object

byte cmd=0;         // a place to put our serial data
byte ch=0;          // global counter for tracking what pin we are on

unsigned long loop_time, last_lp_time, last_chg_time;   // timing variable

void setup() {
    Serial.begin(115200);
    Serial.print("PinChangeInt ReciverReading test");
    Serial.println();            //warm up the serial port

    for (byte i=0; i<RC_COUNT; i++)
    {
        pinMode(pin_rc[i], INPUT);     //set the pin_rc to input
        digitalWrite(pin_rc[i], HIGH); //use the internal pullup resistor
        rc_rise[i] = 0;
        rc_fall[i] = 0;
    }
    PCintPort::attachInterrupt(pin_rc[0], rise,RISING); // attach a pin_rcChange Interrupt to our first pin_rc
    last_chg_time = micros();
    
    for (byte i=0; i<SERVO_COUNT; i++)
    {
        svo[i].attach(pin_servo[i]);    // initialise the servo object
    }
}

void loop() {
    loop_time = millis();    
    
    if((last_lp_time - loop_time)>= PERIOD_LOOP )       // main loop controller
    {
        svo[IND_SVO_FWD].writeMicroseconds(rc_pwm[IND_RC_FWD]);     // write servo output
        svo[IND_SVO_TRN].writeMicroseconds(rc_pwm[IND_RC_TRN]);
        
        cmd=Serial.read();        //while you got some time gimme a systems report
        if (cmd=='p')
        {
            Serial.print("time:\t");
            for (byte i=0; i<PIN_RC_COUNT;i++)
            {
                Serial.print(i,DEC);
                Serial.print(":");
                Serial.print(rc_pwm[i],DEC);
                Serial.print("\t");
            }
            Serial.println();
        }
        cmd=0;
        
        unsigned long time_last = last_chg_time;    // make a snapshot incase inturrupt happened
        unsigned long time_now = micros();    
        if( (time_now > time_last) && ((time_now - time_last) >= RC_MAX_PERD) ) // sometimes 
        {
            //Serial.println("miss!");
            rc_pwm[ch] = 0;
            PCintPort::detachInterrupt(pin_rc[ch]);
            ch++;                     // move to the next pin
            ch %= PIN_RC_COUNT;       // i ranges from 0 to PIN_RC_COUNT
            PCintPort::attachInterrupt(pin_rc[ch], rise,RISING);
            last_chg_time = micros();
        }
      }
        
}


void rise()        // on the rising edge of the currently intresting pin
{
    rc_rise[ch] = micros();
    PCintPort::detachInterrupt(pin_rc[ch]);
    PCintPort::attachInterrupt(pin_rc[ch], fall, FALLING); //attach the falling end
    last_chg_time = rc_rise[ch];
}


void fall()        //on the falling edge of the signal
{
    rc_fall[ch] = micros();
    unsigned int pwm = rc_fall[ch] - rc_rise[ch];
    if( (pwm <= PWM_MAX) && (pwm >= PWM_MIN) )      // simple pwm checker. maybe should move somewhere else
    {
        rc_pwm[ch] = pwm;
    }
    PCintPort::detachInterrupt(pin_rc[ch]);
    last_chg_time = rc_fall[ch];
    ch++;                       // move to the next pin_rc
    ch %= PIN_RC_COUNT;         // i ranges from 0 to PIN_RC_COUNT
    PCintPort::attachInterrupt(pin_rc[ch], rise,RISING);
}
